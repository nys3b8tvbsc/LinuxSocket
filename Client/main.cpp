/* Simple Client.
 * Sends current the date, time(with milliseconds) and own name every n seconds.
*/

#include "clientsocket.h"
#include "message.h"

#include <iostream>
#include <sstream>
#include <unistd.h>

int main(int argc, char* argv[])
{
    if (argc < 4) {
        std::stringstream ss;
        ss << "usage " << argv[0] << " name port timeout";
        std::cerr << ss.str() << std::endl;
        exit(0);
    }
    std::string name = argv[1];
    int port = atoi(argv[2]);
    int timeout = atoi(argv[3]);

    try {
        ClientSocket client(port);
        while (true) {
            client.sendMessage(createMessage(name));
            sleep(timeout);
        }
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}
