#include <ros_mbed_bridge/ros_mbed_bridge.h>

RosMbedBridge::RosMbedBridge(ros::NodeHandle nh, ros::NodeHandle pnh)
{
    nh_ = nh;
    pnh_ = pnh;
}

RosMbedBridge::~RosMbedBridge()
{

}

void RosMbedBridge::cmdCallback(const ros_mbed_bridge::Cmd::ConstPtr msg)
{
    return;
}

void RosMbedBridge::run()
{
    cmd_sub_ = pnh_.subscribe("cmd", 10, &RosMbedBridge::cmdCallback, this);
    server_ptr_ = std::make_shared<UdpServer>(int(SERVER_PORT));
    server_ptr_->registerCallback(std::bind(&RosMbedBridge::receive,this,std::placeholders::_1));
    return;
}

void RosMbedBridge::receive(std::string msg)
{
    using namespace boost::property_tree;
    ptree pt;
    read_json(msg, pt);
    boost::optional<std::string> type_str = pt.get_optional<std::string>("type");
    if(!type_str)
    {
        ROS_WARN_STREAM("Failed to get command type.");
        return;
    }
    if(type_str.get() == "HBT")
    {
        boost::optional<ros_mbed_bridge::HeartBeat> heart_beat = convertHeartBeat(pt);
        if(heart_beat)
        {
            heartbeat_buffer_[heart_beat->device_name] = heart_beat.get();
        }
    }
    return;
}

boost::optional<ros_mbed_bridge::HeartBeat> RosMbedBridge::convertHeartBeat(boost::property_tree::ptree pt)
{
    ros_mbed_bridge::HeartBeat heart_beat;
    heart_beat.header.stamp = ros::Time::now();
    boost::optional<std::string> ip_address = pt.get_optional<std::string>("ip_address");
    if(!ip_address)
    {
        return boost::none;
    }
    heart_beat.ip_address = ip_address.get();
    boost::optional<std::string> device_name = pt.get_optional<std::string>("device_name");
    if(!device_name)
    {
        return boost::none;
    }
    heart_beat.device_name = device_name.get();
    return heart_beat;
}