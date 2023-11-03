/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-valentin.nouri
** File description:
** Client
*/

#pragma once

#include "GameState/GameManager.hpp"
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/asio/io_context.hpp>
#include <iostream>
#include <fstream>
#include <thread>
#include <string>
#include <queue>
#include <mutex>

#define MIN_PORT 1024

#define BUFFER_SIZE 2048

#define DEFAULT_SERVEUR_NAME "localhost"

#define CRLF "\n"

namespace gamestate {
    class GameManager;
}

namespace network {

    class Client {
        public:

            class ClientException : public std::exception {

                public:
                    ClientException(const std::string &comment) noexcept :
                        _error("Client exception : (" + comment + ")")
                    {};

                    const char *what(void) const noexcept {
                        return _error.c_str();
                    }

                private:
                    const std::string _error;
            };

            Client();

            ~Client();

            auto start(const std::string& server, const std::string& port) -> void;

            auto stop(void) -> void;

            auto enqueueMessage(const std::string &message) -> void;

            inline auto getServerName(void) const -> const std::string &
                { return _serverName; };

            inline auto getPort(void) const -> const std::string &
                { return _port; };

        private:
            boost::asio::io_context _ioContext;
            boost::asio::ip::tcp::socket _socket;
            boost::asio::streambuf _readBuffer;
            std::array<char, BUFFER_SIZE> _writeBuffer;
            std::queue<std::string> _messagesQueue;
            std::string _serverName;
            std::string _port;

            auto stopHandler(void) -> void;

            auto asyncRead() -> void;

            auto readHandler(const boost::system::error_code &errorCode,
                const std::size_t &bytesReaded) -> void;

            auto asyncWrite(const std::string &message) -> void;

            auto doWrite(void) -> void;

            auto writeHandler(const boost::system::error_code &errorCode,
                const std::size_t &bytesWrited) -> void;
    };
}

auto operator <<(std::ostream &out, const network::Client &client) -> std::ostream &;
