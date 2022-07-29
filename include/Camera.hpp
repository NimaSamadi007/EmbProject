#ifndef _CAMERA_HPP_
#define _CAMERA_HPP_

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

class Camera{
private:
    cv::Mat current_image;
    int last_num_of_faces;
    cv::CascadeClassifier face_cascade;
    cv::VideoCapture cap;
    MQTTClient client;
public:
    Camera();
    ~Camera();
    void run();
    int detectFaces(cv::Mat frame);
    bool publish(char* topic, char* payload);
    void saveCurrentImage();
};

#endif // _CAMERA_HPP_