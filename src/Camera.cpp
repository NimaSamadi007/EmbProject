#include "Camera.hpp"
#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <cstdlib>
#include <string>
#include <thread>
#include <atomic>
#include <chrono>
#include <cstring>
#include <stdio.h>
#include <ctime>
#include <signal.h>
#include <stdlib.h>
#include "MQTTClient.h"
#include "db_handler.hpp"

Camera::Camera() 
    : last_num_of_faces{0}, cap{0}{
    // create a new MQTT client
    MQTTClient_create(&client, ADDRESS, CLIENTID, MQTTCLIENT_PERSISTENCE_NONE, NULL);
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    conn_opts.username = "face_det";
    conn_opts.password = "qscesz159";
    if (MQTTClient_connect(client, &conn_opts) != MQTTCLIENT_SUCCESS)
        std::cout << "Unable to connect to MQTT broker" << std::endl;


    // load face detection model:
    if(!face_cascade.load("/home/nima/local-libs/opencv/share/opencv4/haarcascades/haarcascade_frontalcatface.xml"))
        std::cout << "Unable to load face detection model" << std::endl;
}

bool Camera::publish(char* topic, char* payload){
    MQTTClient_message pubmsg = MQTTClient_message_initializer;
    pubmsg.payload =  payload;
    pubmsg.payloadlen = strlen(payload);
    pubmsg.qos = 2;
    pubmsg.retained = 0;
    MQTTClient_deliveryToken token;
    MQTTClient_publishMessage(client, topic, &pubmsg, &token);
    MQTTClient_waitForCompletion(client, token, 1000L);
    // printf("Message '%s' with delivery token %d delivered\n", payload, token);
    return true;
}

int Camera::detectFaces(cv::Mat frame){
    cv::Mat frame_gray;
    cv::cvtColor(frame, frame_gray, cv::COLOR_BGR2GRAY);
    cv::equalizeHist(frame_gray, frame_gray);
    std::vector<cv::Rect> faces;
    face_cascade.detectMultiScale(frame_gray, faces);	
    for ( size_t i = 0; i < faces.size(); i++ ){
        cv::putText(frame, 
                std::to_string(i+1),
                cv::Point(faces[i].x+(faces[i].width/2),faces[i].y - 10), 
                cv::FONT_HERSHEY_COMPLEX_SMALL, 
                1.0, 
                cv::Scalar(255,255,255), 
                1, 
                cv:: LINE_AA);
        cv::rectangle(frame, cv::Point(faces[i].x, faces[i].y), 
                      cv::Point(faces[i].x + faces[i].width, faces[i].y + faces[i].height), 
                      cv::Scalar(0, 0, 255), 3, cv::LINE_8);
        cv::Mat faceROI = frame_gray(faces[i] );
    }
	
    // uncomment the following line to display the images
    // cv::imshow("Capture", frame);
    // recievedKey = cv::waitKey(25);
    return (faces.size());
}

void Camera::run(){
    DBHandler db("test", "123456", "sensors");
    char faces[5]; // at most 10^5-1 faces in a frame!
    char database_query[100];

    int num_of_faces;

    if (!cap.isOpened()) {
        std::cerr << "ERROR: Could not open camera" << std::endl;
        return;
    }
    while(1){
    	cap >> current_image;
        num_of_faces = detectFaces(current_image);
        if (num_of_faces != last_num_of_faces){
            // query database:
            // sprintf(database_query, "INSERT INTO camera (num_of_faces) VALUES (%d)", num_of_faces);
            // db.queryDB(database_query);

            // publish to broker:
            // sprintf(faces, "%d", num_of_faces);
            // publish("sensors/faces", faces);
            last_num_of_faces = num_of_faces;
        }
    }
}

void Camera::saveCurrentImage(){
    cv::imwrite("img.jpg", current_image);
    std::cout << "New image saved" << std::endl;
}

Camera::~Camera(){
    MQTTClient_disconnect(client, 1000);
    MQTTClient_destroy(&client);
    cv::destroyAllWindows();
    cap.release();
}
