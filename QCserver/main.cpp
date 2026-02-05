#include <iostream>
#include <QCNetwork/TCPServer.h>

using boost::asio::ip::tcp;

int main(int argc, char* argv[]) {
    QC::TCPServer server{QC::IPV::V4, 8080};

    server.run();
    return 0;
}