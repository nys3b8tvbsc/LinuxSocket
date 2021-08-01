#include "serversocket.h"

#include <cerrno>
#include <cstring>
#include <netdb.h>
#include <stdexcept>
#include <sys/socket.h>
#include <unistd.h>

ServerSocket::ServerSocket(int port)
{
    _socket = socket(AF_INET, SOCK_STREAM, 0);
    if (_socket < 0) {
        throw std::runtime_error(std::string("ERROR opening socket ") + std::strerror(errno));
    }

    sockaddr_in serv_addr;
    bzero(reinterpret_cast<char*>(&serv_addr), sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(static_cast<uint16_t>(port));
    if (bind(_socket, reinterpret_cast<sockaddr*>(&serv_addr), sizeof(serv_addr)) < 0) {
        throw std::runtime_error(std::string("ERROR on binding ") + std::strerror(errno));
    }

    listen(_socket, 5);
}

ServerSocket::~ServerSocket()
{
    close(_socket);
}

int ServerSocket::accept()
{
    int newsocket = ::accept(_socket, nullptr, nullptr);
    if (newsocket < 0) {
        throw std::runtime_error(std::string("ERROR on accept ") + std::strerror(errno));
    }
    return newsocket;
}

std::string receive(int socket)
{
    const size_t buffer_size = 256;
    char buffer[buffer_size] = {};
    auto n = read(socket, buffer, buffer_size);
    if (n < 0) {
        throw std::runtime_error(std::string("ERROR reading from socket ") + std::strerror(errno));
    }
    return std::string(buffer);
}
