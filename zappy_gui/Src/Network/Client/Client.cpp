/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** Client
*/

#include "Network/Client/Client.hpp"
#include "Beans/Bean.hpp"
#include "GameState/GameManager.hpp"
#include <iostream>
#include <string>

// --------------------------------Construction---------------------------------

network::Client::Client()
    : _ioContext(),
      _socket(_ioContext),
      _readBuffer(),
      _writeBuffer(),
      _messagesQueue(){};

// -----------------------------------------------------------------------------

// --------------------------------Destruction----------------------------------

network::Client::~Client()
{
    if (!_ioContext.stopped())
        _ioContext.stop();
    _ioContext.run();
    if (_socket.is_open())
        _socket.close();
}

// -----------------------------------------------------------------------------

// ------------------------------Public methodes--------------------------------

auto network::Client::start(const std::string &server, const std::string &port) -> void
{
    _serverName = server;
    _port = port;

    boost::asio::ip::tcp::resolver resolver(_ioContext);
    boost::asio::ip::tcp::resolver::results_type endpoints = resolver.resolve(server, port);

    try {
        boost::asio::connect(_socket, endpoints);
    } catch (const std::exception &exception) {
        throw ClientException("Connect error");
    }

    std::thread clientThread([this]() {
        asyncRead();
        _ioContext.run();
    });
    clientThread.detach();
}

auto network::Client::stop(void) -> void
{
    if (!_socket.is_open())
        throw ClientException("Can't stop disconnected client");

    _ioContext.post(std::bind(&Client::stopHandler, this));
}

auto network::Client::enqueueMessage(const std::string &message) -> void
{
    if (!_socket.is_open())
        throw ClientException("Can't enqueue message to disconnected client");

    _ioContext.post(std::bind(&Client::asyncWrite, this, message));
}

// -----------------------------------------------------------------------------

// ------------------------------Private methodes-------------------------------

auto network::Client::stopHandler(void) -> void
{
    if (_socket.is_open())
        _socket.close();
}

auto network::Client::asyncRead() -> void
{
    boost::asio::async_read_until(_socket, _readBuffer, CRLF,
    std::bind(&network::Client::readHandler, this, std::placeholders::_1, std::placeholders::_2));
}

auto network::Client::readHandler(const boost::system::error_code &errorCode,
const std::size_t &bytesReaded) -> void
{
    if (errorCode) {
        if (errorCode == boost::asio::error::eof) {
            // std::cout << "Connection closed by remote host." << std::endl;
            if (_socket.is_open())
                _socket.close();
        } else {
            // std::cerr << "Read error : " << errorCode.message() << std::endl;
            if (_socket.is_open())
                _socket.close();
        }
        return;
    }

    std::string message(boost::asio::buffers_begin(_readBuffer.data()),
    boost::asio::buffers_begin(_readBuffer.data()) + bytesReaded);
    Bean<gamestate::GameManager>::getInstance().handleMessage(message);
    _readBuffer.consume(bytesReaded);
    asyncRead();
}

auto network::Client::asyncWrite(const std::string &message) -> void
{
    bool write_in_progress = !_messagesQueue.empty();
    _messagesQueue.push(message + CRLF);
    if (!write_in_progress)
        doWrite();
}

auto network::Client::doWrite(void) -> void
{
    boost::asio::async_write(_socket,
    boost::asio::buffer(_messagesQueue.front()),
    std::bind(&Client::writeHandler, this,
    std::placeholders::_1, std::placeholders::_2));
}

auto network::Client::writeHandler(const boost::system::error_code &errorCode,
const std::size_t &bytesWrited) -> void
{
    if (errorCode) {
        // std::cerr << "Write error : " << errorCode.message() << std::endl;
        if (_socket.is_open())
            _socket.close();
        return;
    }

    (void)bytesWrited;
    _messagesQueue.pop();
    if (!_messagesQueue.empty())
        doWrite();
}

// -----------------------------------------------------------------------------

auto operator<<(std::ostream &out, const network::Client &client) -> std::ostream &
{
    out << "Client :" << std::endl
        << "port = " << client.getPort() << std::endl
        << "serverName = " << client.getServerName();
    return out;
}
