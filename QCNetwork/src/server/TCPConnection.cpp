#include "QCNetwork/server/TCPConnection.h"
#include <iostream>

namespace QC {
    void TCPConnection::asyncRead()
    {  
        asio::async_read_until(_socket, _streamBuf, '\n', [self = shared_from_this()](boost::system::error_code ec, size_t bytesTransferred){
            self->onRead(ec, bytesTransferred);
        });
    }

    void TCPConnection::onRead(boost::system::error_code ec, size_t bytesTransferred)
    {
        if (ec) {
            _socket.close();

            _errorHandler();
            return;
        }

        std::stringstream message;
        message << _username << ": " << std::istream(&_streamBuf).rdbuf(); // rdbuf consumes the buffer

        _msgHandler(message.str());
        asyncRead();
    }

    void TCPConnection::asyncWrite()
    {
        asio::async_write(_socket, asio::buffer(_outgoingMsgs.front()), [self = shared_from_this()](boost::system::error_code ec, size_t bytesTransferred){
            self->onWrite(ec, bytesTransferred);
        });
    }

    void TCPConnection::onWrite(boost::system::error_code ec, size_t bytesTransferred)
    {
        if (ec) {
            _socket.close();

            _errorHandler();
            return;
        }

        _outgoingMsgs.pop();
        if (!_outgoingMsgs.empty()) {
            asyncWrite();
        }
    }

     TCPConnection::TCPConnection(asio::ip::tcp::socket&& socket) : _socket(std::move(socket))
    {
        boost::system::error_code ec;
        std::stringstream name;

        name << _socket.remote_endpoint();
        _username = name.str();

    }

    tcp::socket& TCPConnection::getSocket()
    {
        return _socket;
    }

    void TCPConnection::start(msgHandler&& msgHandler, errorHandler&& errorHandler)
    {
        _msgHandler = std::move(msgHandler);
        _errorHandler = std::move(errorHandler);
        asyncRead();
    }

    void TCPConnection::post(const std::string& message)
    {
        bool queueIdle = _outgoingMsgs.empty();
        _outgoingMsgs.push(message);

        if (queueIdle) {
            asyncWrite();
        }
    }

    TCPConnection::tcpShPtr TCPConnection::create(asio::ip::tcp::socket&& socket)
    {
        return std::make_shared<TCPConnection>(std::move(socket));
    }
}


