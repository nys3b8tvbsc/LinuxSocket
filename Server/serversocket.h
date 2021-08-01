#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H

#include <string>

/*!
 * \brief Minimalistic TCP server.
 */
class ServerSocket {
public:
    /*!
     * \brief Init _socket bind to localhost:port and listen.
     * Raises std::runtime_error.
     * \param port Port to bind
     */
    ServerSocket(int port);
    ~ServerSocket();
    /*!
     * \brief Accept new connection.
     * Raises std::runtime_error/
     * \return int New linux socket binded to client
     */
    int accept();

private:
    int _socket; //! Linux socket.
};

/*!
 * \brief Receives message from client connected to socket.
 * Raises std::runtime_error.
 * \param socket Linux socket binded to client.
 * \return std::string with message. Empty string if connection closed.
 */
std::string receive(int socket);

#endif // SERVERSOCKET_H
