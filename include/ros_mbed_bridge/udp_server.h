#ifndef UDP_SERVER_H_INCLUDED
#define UDP_SERVER_H_INCLUDED

//headers in STL
#include <functional>
#include <vector>
#include <mutex>
#include <iostream>

//headers in boost
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>

#define BUFFER_SIZE 1024

class UdpServer
{
public:
    UdpServer(int port);
    ~UdpServer();
    void registerCallback(std::function<void(std::string)> func);
    void run();
    const int port;
private:
    std::vector<std::function<void(std::string)> > callback_funcs_;
    boost::array<char,BUFFER_SIZE> recv_buf_;
    std::mutex mtx_;
    void receive(const boost::system::error_code&, std::size_t len);
};

#endif  //UDP_SERVER_H_INCLUDED