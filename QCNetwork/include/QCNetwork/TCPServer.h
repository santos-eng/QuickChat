#pragma once
#include <boost/asio.hpp>

namespace QC {
    enum class IPV {
        V4,
        V6
    };

    class TCPServer {
        IPV _ipversion;
        int _port;

        boost::asio::io_context _ioContext;
        boost::asio::ip::tcp::acceptor _acceptor;

        void startAccept();

    public:
        TCPServer(IPV ipv, int port);

        int run();
    };
}