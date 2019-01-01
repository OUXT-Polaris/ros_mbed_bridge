#ifndef UDP_CLIENT_H_INCLUDED
#define UDP_CLIENT_H_INCLUDED

//headers in STL
#include <iostream>

//headers in boost
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>

#define BUFFER_SIZE 1024

class UdpClient
{
public:
    UdpClient(std::string ip_address,int port);
    ~UdpClient();
    void send(std::string data);
    const std::string ip_address;
    const int port;
private:
    boost::asio::ip::udp::endpoint endpoint_;
    boost::shared_ptr<boost::asio::ip::udp::socket> socket_ptr_;
    boost::asio::io_service io_service_;
};
#endif  //UDP_CLIENT_H_INCLUDED