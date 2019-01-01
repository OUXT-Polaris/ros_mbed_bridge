#ifndef ROS_MBED_BRIDGE_H_INCLUDED
#define ROS_MBED_BRIDGE_H_INCLUDED

//headers in ROS
#include <ros/ros.h>

//headers in this package
#include <ros_mbed_bridge/udp_server.h>
#include <ros_mbed_bridge/udp_client.h>
#include <ros_mbed_bridge/Cmd.h>

class RosMbedBridge
{
public:
    RosMbedBridge(ros::NodeHandle nh, ros::NodeHandle pnh);
    ~RosMbedBridge();
private:
    ros::NodeHandle nh_;
    ros::NodeHandle pnh_;
};

#endif  //ROS_MBED_BRIDGE_H_INCLUDED