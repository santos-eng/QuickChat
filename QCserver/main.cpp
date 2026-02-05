#include <iostream>
#include <QCNetwork/server/TCPServer.h>

using boost::asio::ip::tcp;

int main(int argc, char* argv[]) {
    QC::TCPServer server{QC::IPV::V4, 8080};

    server.onJoin = [](QC::TCPConnection::tcpShPtr server) {
        std::cout << server->getUsername() << " has joined the server.\n";
    };

    server.onLeave = [](QC::TCPConnection::tcpShPtr server) {
        std::cout << server->getUsername() << " has left the server.\n";
    };

    server.onClientMsg = [&server](const std::string& message) {
        server.broadcast(message);
    };

    server.run();
    return 0;
}