#include <iostream>

#include "Server.h"

int main() {
    network::Server server;
    auto adress = server.get_adress();
    std::cout << "IP: " << adress.first.toString() << std::endl
              << "PORT: " << adress.second << std::endl;
    server.run();
}
