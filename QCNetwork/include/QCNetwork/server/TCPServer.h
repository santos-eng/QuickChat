#pragma once
#include <boost/asio.hpp>
#include "TCPConnection.h"
#include <vector>
#include <functional>
#include <optional>
#include <unordered_set>

namespace QC {
    namespace asio = boost::asio;

    enum class IPV {
        V4,
        V6
    };

    class TCPServer {
        using onJoinHandler = std::function<void(TCPConnection::tcpShPtr)>;
        using onLeaveHandler = std::function<void(TCPConnection::tcpShPtr)>;
        using onClientMsgHandler = std::function<void(std::string)>;

        IPV _ipversion;
        int _port;

        asio::io_context _ioContext;
        asio::ip::tcp::acceptor _acceptor;

        std::unordered_set<TCPConnection::tcpShPtr> _connections;
        std::optional<asio::ip::tcp::socket> _socket;

        void startAccept();

    public:
        onJoinHandler onJoin;
        onLeaveHandler onLeave;
        onClientMsgHandler onClientMsg;

        TCPServer(IPV ipv, int port);

        int run();

        void broadcast(const std::string& message);

        
    };
}