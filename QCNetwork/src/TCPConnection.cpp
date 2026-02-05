#include "QCNetwork/TCPConnection.h"
#include <iostream>

namespace QC {
     TCPConnection::TCPConnection(boost::asio::io_context& ioContext) : _socket(ioContext)
    {
        
    }

    tcp::socket& TCPConnection::getSocket()
    {
        return _socket;
    }

    void TCPConnection::start()
    {
        // Make sure to hold message, even if initial goes out of scope
        auto strongThis = shared_from_this();

        // Write connection message to socket
        boost::asio::async_write(_socket, boost::asio::buffer(_message), 
            [strongThis](const boost::system::error_code& error, size_t bytesTransferred){
                if (error) {
                    std::cout << "Failed to send message\n";
                } else {
                    std::cout << "Sent " << bytesTransferred << " bytes of data\n";
                }
            });
    }

    TCPConnection::tcpShPtr TCPConnection::create(boost::asio::io_context& ioContext)
    {
        return std::make_shared<TCPConnection>(ioContext);
    }
}


