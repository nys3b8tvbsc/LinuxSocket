#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <string>

/*!
 * \brief Class that sends messages to the localhost:port.
 */
class ClientSocket {
public:
    /*!
     * \brief Initialize _socket and connect to localhost:port.
     * Raises std::runtime_error if can't init socket or connect.
     * \param port Server port.
     */
    ClientSocket(int port);
    ~ClientSocket();

    /*!
     * \brief Sends message to localhost:port.
     * Raises std::runtime_error if can't send.
     * \param message Message to send.
     */
    void sendMessage(const std::string& message);

private:
    int _socket; //! Linux socket.
};

#endif // CLIENTSOCKET_H
