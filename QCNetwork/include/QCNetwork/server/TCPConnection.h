#pragma once
#include <boost/asio.hpp>
#include <memory>
#include <string>
#include <queue>

namespace QC {
    using boost::asio::ip::tcp;
    namespace asio = boost::asio;

    class TCPConnection : public std::enable_shared_from_this<TCPConnection> {
        tcp::socket _socket;
        std::string _username;

        std::queue<std::string> outgoingMsgs;
        asio::streambuf _streamBuf{65536}; // Hold incoming messages

        // Waiting for new client msg
        void asyncRead();
        void onRead(boost::system::error_code ec, size_t bytesTransferred);

        void asyncWrite();
        void onWrite(boost::system::error_code ec, size_t bytesTransferred);

        
    public:
        explicit TCPConnection(asio::ip::tcp::socket&& socket);

        tcp::socket& getSocket();

        void start();
        void post(const std::string& message);

        using tcpShPtr = std::shared_ptr<TCPConnection>;
        static tcpShPtr create(asio::ip::tcp::socket&& socket);
    };
}