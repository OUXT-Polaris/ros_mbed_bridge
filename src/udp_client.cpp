#include <ros_mbed_bridge/udp_client.h>

UdpClient::UdpClient(std::string ip_address,int port) : ip_address(ip_address), port(port)
{
    using boost::asio::ip::udp;
    boost::shared_ptr<udp::socket> socket_ptr(new udp::socket(io_service_,endpoint_));
    socket_ptr_ = socket_ptr;
}

UdpClient::~UdpClient()
{

}

void UdpClient::send(std::string data)
{
    socket_ptr_->send_to(boost::asio::buffer(data), endpoint_);
    return;
}