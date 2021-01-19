#include <cstdlib>
#include <iostream>
#include <cctype>

#include "include/playing-field.h"
#include "include/server-loop.h"

int parse_arg(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: async_tcp_echo_server <port> <world> <max attempts>\n";
        return -1;
    }

    std::string port_str(argv[1]);
    if (!std::all_of(port_str.begin(), port_str.end(), [](const auto i){ return std::isdigit(i); })) {
        std::cerr << "Port must be int!\n";
        return -1;
    }
    auto port = std::atoi(argv[1]);

    std::string world_str(argv[2]);
    if (!std::all_of(world_str.begin(), world_str.end(), [](const auto i){ return std::isalpha(i); })) {
        std::cerr << "Word must contain only alphabet symbol!\n";
        return -1;
    }
    std::transform(world_str.begin(), world_str.end(), world_str.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    world.fill_field(world_str);

    std::string attempts_str(argv[3]);
    if (!std::all_of(attempts_str.begin(), attempts_str.end(), [](const auto i){ return std::isdigit(i); })) {
        std::cerr << "Max attmepts must be int!\n";
        return -1;
    }
    max_attempts = std::atoi(argv[3]);

    return port;
}

int main(int argc, char* argv[]) {

    try {
        auto port = parse_arg(argc, argv);
        if (port < 0) {
            return(1);
        }

        boost::asio::io_service io_service;
        server s(io_service, port);

        io_service.run();
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
