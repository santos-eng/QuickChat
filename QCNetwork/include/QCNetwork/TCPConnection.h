#pragma once
#include <boost/asio.hpp>
#include <memory>
#include <string>

namespace QC {
    using boost::asio::ip::tcp;

    class TCPConnection {
        tcp::socket _socket;
        std::string _message{"hello client, testing\n"};

        explicit TCPConnection(boost::asio::io_context& ioContext);

        
    public:
        tcp::socket& getSocket();

        void start();

        using tcpShPtr = std::shared_ptr<TCPConnection>;

        static tcpShPtr create(boost::asio::io_context& ioContext);
    };
}