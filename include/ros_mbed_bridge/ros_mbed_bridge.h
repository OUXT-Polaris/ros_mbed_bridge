#ifndef ROS_MBED_BRIDGE_H_INCLUDED
#define ROS_MBED_BRIDGE_H_INCLUDED

#define SERVER_PORT

//headers in ROS
#include <ros/ros.h>

//headers in this package
#include <ros_mbed_bridge/udp_server.h>
#include <ros_mbed_bridge/udp_client.h>
#include <ros_mbed_bridge/Cmd.h>
#include <ros_mbed_bridge/HeartBeatStatus.h>

//headers in STL
#include <map>
#include <memory>

//headers in boost
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include <boost/optional.hpp>

namespace ros_mbed_bridge
{
    constexpr uint8_t CMD_HBT = 0;
    constexpr uint8_t CMD_CMD = 1;
}

class RosMbedBridge
{
public:
    RosMbedBridge(ros::NodeHandle nh, ros::NodeHandle pnh);
    ~RosMbedBridge();
    void run();
private:
    ros::NodeHandle nh_;
    ros::NodeHandle pnh_;
    ros::Subscriber cmd_sub_;
    void cmdCallback(const ros_mbed_bridge::Cmd::ConstPtr msg);
    std::shared_ptr<UdpServer> server_ptr_;
    void receive(std::string msg);
    boost::optional<ros_mbed_bridge::HeartBeat> convertHeartBeat(boost::property_tree::ptree pt);
    std::map<std::string,ros_mbed_bridge::HeartBeat> heartbeat_buffer_;
};

#endif  //ROS_MBED_BRIDGE_H_INCLUDED