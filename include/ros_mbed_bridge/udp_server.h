#ifndef UDP_SERVER_H_INCLUDED
#define UDP_SERVER_H_INCLUDED

//headers in STL
#include <functional>
#include <vector>
#include <mutex>

//headers in boost
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/shared_ptr.hpp>

#define BUFFER_SIZE 1024

class UdpServer
{
public:
    UdpServer(int port);
    ~UdpServer();
    void registerCallback(std::function<void(boost::property_tree::ptree)> func);
    void run();
    const int port;
private:
    std::vector<std::function<void(boost::property_tree::ptree)> > callback_funcs_;
    boost::array<char,BUFFER_SIZE> recv_buf_;
    std::mutex mtx_;
    void receive(const boost::system::error_code&, std::size_t len);
};

#endif  //UDP_SERVER_H_INCLUDED