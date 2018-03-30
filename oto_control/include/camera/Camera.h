#pragma once

#include <ros/ros.h>
#include <string>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <camera/withrobot_camera.hpp>
#include <camera/withrobot_utility.hpp>

using namespace std;

class CameraController{
    private:
        ros::NodeHandle n;
        const char* devPath = "/dev/video1";
    public:
        CameraController();
        ~CameraController();
        bool Initialize();

};
