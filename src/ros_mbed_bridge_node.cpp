// headers for ros
#include <ros/ros.h>

//headers in this package
#include <ros_mbed_bridge/ros_mbed_bridge.h>

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "ros_mbed_bridge_node");
    ros::NodeHandle nh;
    ros::NodeHandle pnh;
    RosMbedBridge bridge(nh,pnh);
    bridge.run();
    ros::spin();
    return 0;
}