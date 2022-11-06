#include "main.hpp"

#include "kernel/sockets/clients/inc/clients.hpp"
#include "kernel/sockets/servers/inc/servers.hpp"

int main(int arc, char* argv[])
{
    Systems::Informations::CPUs::CPU_Information CPU_Information;

    Systems::Informations::Motherboards::Motherboard_Information Motherboard_Information;

    string host = "127.0.0.1";
    int server_port = 10000;
    int client_port = 10001;

    Kernel::Sockets::Clients::Client client(
        host,
        client_port
    );
    Kernel::Sockets::Servers::Server server(
        host,
        server_port
    );

    server.start();

    // client.create_connection();
    // client.write();

    return 0;
}