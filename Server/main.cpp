/* A simple TCP server.
 * Recieves messages and saves them to log.txt.
 */
#include <fstream>
#include <iostream>
#include <string>
#include <thread>

#include "serversocket.h"

int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cerr << "ERROR, no port provided"
                  << std::endl;
        exit(1);
    }
    int port = atoi(argv[1]);

    try {
        ServerSocket server(port);
        std::ofstream log("log.txt");
        while (true) {
            int new_socket = server.accept();

            std::thread([new_socket, &log]() {
                try {
                    while (true) {
                        auto message = receive(new_socket);
                        if (message.empty()) {
                            return;
                        }
                        log << message + '\n';
                        log.flush();
                    }
                } catch (const std::runtime_error& e) {
                    std::cerr << e.what() << std::endl;
                }
            }).detach();
        }
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}
