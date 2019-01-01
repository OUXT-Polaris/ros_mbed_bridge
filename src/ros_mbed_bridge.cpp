#include <ros_mbed_bridge/ros_mbed_bridge.h>

RosMbedBridge::RosMbedBridge(ros::NodeHandle nh, ros::NodeHandle pnh)
{
    nh_ = nh;
    pnh_ = pnh;
}

RosMbedBridge::~RosMbedBridge()
{

}