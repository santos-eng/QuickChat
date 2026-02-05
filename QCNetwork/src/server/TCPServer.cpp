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
        // Creating a connection
        auto connection = TCPConnection::create(_ioContext);

        _connections.push_back(connection);

        // asycnhronously connect the connecti onl
        _acceptor.async_accept(connection->getSocket(), 
            [connection, this](const boost::system::error_code& error){
                if (!error) {
                    connection->start();
                }

                //Start new connection 
                startAccept(); 
            });
    }

    template<typename T>
    inline void TCPServer::writeToConnection(int connectionIdx, const T & message)
    {
    }
    
    template<typename T>
    inline void TCPServer::registerListenCallback(listenCallback<T> callback)
    {
}
}


