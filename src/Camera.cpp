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


#define ADDRESS     "localhost"
#define CLIENTID    "Face1"

using namespace cv;
using namespace std;

int detectAndDisplay( Mat frame );
CascadeClassifier face_cascade;
MQTTClient client;

void sigintHandler(int dummy){
    printf("\nSIGINT received and handled\n");
    MQTTClient_disconnect(client, 1000);
    MQTTClient_destroy(&client);
    exit(0);
}

void publish(MQTTClient client, char* topic, char* payload) {
    MQTTClient_message pubmsg = MQTTClient_message_initializer;
    pubmsg.payload =  payload;
    pubmsg.payloadlen = strlen(payload);
    pubmsg.qos = 2;
    pubmsg.retained = 0;
    MQTTClient_deliveryToken token;
    MQTTClient_publishMessage(client, topic, &pubmsg, &token);
    MQTTClient_waitForCompletion(client, token, 1000L);
    printf("Message '%s' with delivery token %d delivered\n", payload, token);
}

int main()
{
    // handling sigint
    signal(SIGINT, sigintHandler);

    // setting up MQTT 
    MQTTClient_create(&client, ADDRESS, CLIENTID, MQTTCLIENT_PERSISTENCE_NONE, NULL);
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    conn_opts.username = "face_det";
    conn_opts.password = "qscesz159";

    if (MQTTClient_connect(client, &conn_opts) != MQTTCLIENT_SUCCESS){
        printf("Failed to connect\n");
        exit(-1);
    }



    cv::VideoCapture camera(0);
    if (!camera.isOpened()) {
        std::cerr << "ERROR: Could not open camera" << std::endl;
        return 1;
    }

    if( !face_cascade.load( "/home/nima/local-libs/opencv/share/opencv4/haarcascades/haarcascade_frontalcatface.xml" ) )
    {
        cout << "--(!)Error loading face cascade\n";
        return -1;
    };

	Mat frame;
    // int recievedKey;
    int preNumberOfFaces = 0;
    int numberOfFaces = 0;
    float temp;

    char faces[5]; // at most 10^5-1 faces in a frame!
    char temp_str[10];

    while(1){
    	camera >> frame;
        numberOfFaces = detectAndDisplay(frame);
        if (preNumberOfFaces != numberOfFaces){
            sprintf(faces, "%d", numberOfFaces);
            publish(client, "sensors/faces", faces);

            preNumberOfFaces = numberOfFaces;

            FILE* fptr = fopen("/sys/class/thermal/thermal_zone2/temp", "r");
            fscanf(fptr, "%f", &temp);

            sprintf(temp_str, "%f", temp/1000);
            fclose(fptr);
            publish(client, "sensors/temp", temp_str);
        }
        // recievedKey = waitKey(25);
		// if (recievedKey == int('q'))
		// 	break;
    }

    return 0;
}


int detectAndDisplay( Mat frame )
{

    Mat frame_gray;
    cvtColor( frame, frame_gray, COLOR_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );
    std::vector<Rect> faces;
    face_cascade.detectMultiScale( frame_gray, faces );	
    for ( size_t i = 0; i < faces.size(); i++ )
    {

	cv::putText(frame, 
            to_string(i+1),
            cv::Point(faces[i].x+(faces[i].width/2),faces[i].y - 10), 
            cv::FONT_HERSHEY_COMPLEX_SMALL, 
            1.0, 
            cv::Scalar(255,255,255), 
            1, 
            cv:: LINE_AA);
	 

	rectangle( frame, Point(faces[i].x, faces[i].y), Point(faces[i].x + faces[i].width, faces[i].y + faces[i].height), Scalar(0, 0, 255), 3, LINE_8);
        Mat faceROI = frame_gray( faces[i] );
	}
	
    // uncomment the following line to display the images
    // imshow( "Capture - Face detection", frame );
    return (faces.size());
}
