#pragma once
#include <boost/asio.hpp>
#include <memory>
#include <string>

namespace QC {
    using boost::asio::ip::tcp;

class TCPConnection : public std::enable_shared_from_this<TCPConnection> {
    tcp::socket _socket;
    std::string _message{"hello client, testing\n"};

    

    
public:
    explicit TCPConnection(boost::asio::io_context& ioContext);

    tcp::socket& getSocket();

    void start();

    using tcpShPtr = std::shared_ptr<TCPConnection>;
    static tcpShPtr create(boost::asio::io_context& ioContext);
};
}