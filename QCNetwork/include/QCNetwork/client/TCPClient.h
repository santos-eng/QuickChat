#pragma once
#include <boost/asio.hpp>
#include <queue>

namespace QC {
    namespace asio = boost::asio;
    using msgHandler = std::function<void(std::string)>;

    class TCPClient {
        asio::io_context _ioContext{};
        asio::ip::tcp::socket _socket; 

        asio::ip::tcp::resolver::results_type _endpoints;

        asio::streambuf _streamBuf{65536};
        std::queue<std::string> _outgoingMsgs;

        void asyncRead();
        void onRead(boost::system::error_code ec, size_t bytesTransferred);
        void asyncWrite();
        void onWrite(boost::system::error_code ec, size_t bytesTransferred);

    public:
        TCPClient(const std::string& address, int port);

        void run();  
        void stop();
        void post(const std::string& message);

        msgHandler onMessage;
    };
}