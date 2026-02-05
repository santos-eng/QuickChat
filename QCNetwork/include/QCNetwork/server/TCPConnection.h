#pragma once
#include <boost/asio.hpp>
#include <memory>
#include <string>
#include <queue>
#include <functional>

namespace QC {
    using boost::asio::ip::tcp;
    namespace asio = boost::asio;

    using msgHandler = std::function<void(std::string)>;
    using errorHandler = std::function<void()>;

    class TCPConnection : public std::enable_shared_from_this<TCPConnection> {
        tcp::socket _socket;
        std::string _username;

        std::queue<std::string> _outgoingMsgs;
        asio::streambuf _streamBuf{65536}; // Hold incoming messages

        void asyncRead();
        void onRead(boost::system::error_code ec, size_t bytesTransferred);

        void asyncWrite();
        void onWrite(boost::system::error_code ec, size_t bytesTransferred);

        msgHandler _msgHandler;
        errorHandler _errorHandler;
        
    public:
        explicit TCPConnection(asio::ip::tcp::socket&& socket);

        tcp::socket& getSocket();

        void start(msgHandler&& msgHandler, errorHandler&& errorHandler);
        void post(const std::string& message);

        inline const std::string& getUsername() const {
            return _username;
        }

        // FACTORY METHOD
        using tcpShPtr = std::shared_ptr<TCPConnection>;
        static tcpShPtr create(asio::ip::tcp::socket&& socket); 
    };
}