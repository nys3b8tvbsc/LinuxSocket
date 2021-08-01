#include "clientsocket.h"
#include <cerrno>
#include <cstring>
#include <netdb.h>
#include <stdexcept>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

ClientSocket::ClientSocket(int port)
{
    _socket = socket(AF_INET, SOCK_STREAM, 0);
    if (_socket < 0) {
        throw std::runtime_error(std::string("Error opening socket ") + std::strerror(errno));
    }

    hostent* server = gethostbyname("localhost");
    if (server == nullptr) {
        throw std::runtime_error("ERROR, no such host");
    }

    //Create and init serv_addr struct;
    sockaddr_in serv_addr;
    bzero(reinterpret_cast<char*>(&serv_addr), sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy(reinterpret_cast<char*>(server->h_addr),
        reinterpret_cast<char*>(&serv_addr.sin_addr.s_addr),
        static_cast<size_t>(server->h_length));
    serv_addr.sin_port = htons(static_cast<uint16_t>(port));

    if (connect(_socket, reinterpret_cast<sockaddr*>(&serv_addr), sizeof(serv_addr)) < 0) {
        throw std::runtime_error(std::string("ERROR connecting ") + std::strerror(errno));
    }
}

ClientSocket::~ClientSocket()
{
    close(_socket);
}

void ClientSocket::sendMessage(const std::string& message)
{
    auto n = write(_socket, message.c_str(), message.length());
    if (n < 0) {
        throw std::runtime_error(std::string("ERROR writing to socket ") + std::strerror(errno));
    }
}
