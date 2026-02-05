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
        // Write connection message to socket
        boost::asio::async_write(socket, boost::asio::buffer(_message), 
            [this](const boost::system::error_code& error, size_t bytesTransferred){
                if (error) {
                    std::cout << "Failed to send message\n";
                } else {
                    std::cout << "Sent " << bytesTransferred << " bytes of data\n";
                }
            });
    }

    TCPConnection::tcpShPtr TCPConnection::create(boost::asio::io_context& ioContext)
    {
        return tcpShPtr(new TCPConnection(ioContext));
    }
}


