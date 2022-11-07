#include "main.hpp"

#include "kernel/sockets/clients/inc/clients.hpp"
#include "kernel/sockets/servers/inc/servers.hpp"

#include "communicators/web_interfaces/inc/web_interfaces.hpp"

int main(int arc, char* argv[])
{
    ifstream config_file("../config.json");

    json config = json::parse(config_file);

    Communicators::WEB_Interfaces::WEB_Interface_Communicator communicator(
        config["web_interface"]
    );

    communicator.create_connection();

    return 0;
}