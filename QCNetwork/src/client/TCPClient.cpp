#include "QCNetwork/client/TCPClient.h"

namespace QC {
    TCPClient::TCPClient(const std::string& address, int port) : _socket(_ioContext)
    {
        asio::ip::tcp::resolver resolver{_ioContext};
        _endpoints = resolver.resolve(address, std::to_string(port));
    }

    void TCPClient::run()
    {
        asio::async_connect(_socket, _endpoints, [this](boost::system::error_code ec, asio::ip::tcp::endpoint ep){
            if (!ec) {
                asyncRead();
            }

            _ioContext.run(); // Will wait indefintely, waiting for message
        });

        _ioContext.run();
    }

    void TCPClient::stop()
    {
        boost::system::error_code ec;
        _socket.close(ec);

        if (ec) {

        }
    }

    void TCPClient::post(const std::string & message)
    {
        bool queueIdle = _outgoingMsgs.empty();
        _outgoingMsgs.push(message);

        if (queueIdle) {
            asyncWrite();
        }
    }

    void TCPClient::asyncRead()
    {
        asio::async_read_until(_socket, _streamBuf, "\n", [this](boost::system::error_code ec, size_t bytesTransferred) {
            onRead(ec, bytesTransferred);
        });
    }

    void TCPClient::onRead(boost::system::error_code ec, size_t bytesTransferred)
    {
        if (ec) {
            stop();
            return;
        }

        std::stringstream message;
        message << std::istream{&_streamBuf}.rdbuf();
        onMessage(message.str());
        asyncRead();
    }

    void TCPClient::asyncWrite()
    {
        asio::async_write(_socket, asio::buffer(_outgoingMsgs.front()), [this](boost::system::error_code ec, size_t bytesTransferred) {
            onWrite(ec, bytesTransferred);
        });
    }

    void TCPClient::onWrite(boost::system::error_code ec, size_t bytesTransferred)
    {
        if (ec) {
            stop();
            return;
        }

        _outgoingMsgs.pop();
        
        if (!_outgoingMsgs.empty()) {
            asyncWrite();
        }
    }
}
    
