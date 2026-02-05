#pragma once
#include <boost/asio.hpp>
#include "TCPConnection.h"
#include <vector>
#include <functional>


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

        std::vector<TCPConnection::tcpShPtr> _connections;

        void startAccept();

    public:
        TCPServer(IPV ipv, int port);

        int run();

        template <typename T>
        void writeToConnection(int connectionIdx, const T& message);

        template<typename T>
        using listenCallback = std::function<void(int, const T&)>;

        // Interface to write to a connection
        template <typename T>
        void registerListenCallback(listenCallback<T> callback);
    };
}