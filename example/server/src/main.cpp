
#include <iostream>
#include <memory>

#include "server.hpp"

int main(int argc, char* argv[])
{
    try
    {
        if ( argc != 2 )
        {
            std::cerr << "Usage: server <port>\n";
            return 1;
        }

        ld_server::Server server(std::atoi(argv[1]));
        
        server.init();
        std::cout << "[Start Server]\n";
        server.run();


    } catch(std:: exception& e)
    {
        std::cerr << "Exception: " << e.what() << '\n';
    }

    return 0;
}