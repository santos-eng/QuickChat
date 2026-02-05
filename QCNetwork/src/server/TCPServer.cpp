#include "QCNetwork/server/TCPServer.h"
#include <iostream>

namespace QC {
    using boost::asio::ip::tcp;

    TCPServer::TCPServer(IPV ipv, int port) : _ipversion(ipv), _port(port),
        _acceptor(_ioContext, tcp::endpoint(ipv == IPV::V4 ? tcp::v4() : tcp::v6(), _port))
    {

    }

    int TCPServer::run()
    {
        try {
            startAccept();
            _ioContext.run();
        } catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
            return -1;
        }
        return 0;
    }

    
    void TCPServer::startAccept()
    {
        // Starting to accept (waiting for connection) create waiting socket
        _socket.emplace(_ioContext); 

        _acceptor.async_accept(*_socket, [this](const boost::system::error_code& error){

                // Creating a connection
                auto connection = TCPConnection::create(std::move(*_socket));

                if (onJoin) {
                    onJoin(connection);
                }


                _connections.insert(connection); 

                if (!error) {
                    connection->start();
                }

                //Start new connection 
                startAccept(); 
        });
    }

    void TCPServer::broadcast(const std::string & message)
    {
        for (auto& connection : _connections) {
            connection->post(message);
        }
    }
}



