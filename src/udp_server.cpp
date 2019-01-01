#include <ros_mbed_bridge/udp_server.h>

UdpServer::UdpServer(int port): port(port)
{

}

UdpServer::~UdpServer()
{

}

void UdpServer::run()
{
    using boost::asio::ip::udp;
    boost::asio::io_service io_service;
    mtx_.lock();
    try
    {
        udp::socket socket(io_service, udp::endpoint(udp::v4(), port));
        udp::endpoint remote_endpoint;
        boost::system::error_code error;
        socket.async_receive_from(boost::asio::buffer(recv_buf_), remote_endpoint, boost::bind(&UdpServer::receive,this,_1,_2));
    }
    catch(std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    io_service.run();
    mtx_.unlock();
    return;
}

void UdpServer::registerCallback(std::function<void(std::string)> func)
{
    mtx_.lock();
    callback_funcs_.push_back(func);
    mtx_.unlock();
    return;
}

void UdpServer::receive(const boost::system::error_code&, std::size_t len)
{
    for(auto func_ptr = callback_funcs_.begin(); func_ptr != callback_funcs_.end(); func_ptr++)
    {
        std::function<void(std::string)> func = *func_ptr;
        func(recv_buf_.data());
    }
    return;
}