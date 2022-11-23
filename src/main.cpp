#include "main.hpp"

#include "communicators/web_interfaces/inc/web_interfaces.hpp"
#include "kernel/sockets/clients/inc/clients.hpp"

int main(int arc, char* argv[])
{
    ifstream config_file("../config.json");

    json config = json::parse(config_file);
    
    string host = config["web_interface"]["host"];
    int port = config["web_interface"]["port"];

    Kernel::Sockets::Clients::Client client(
        host,
        port
    );

    client.create_connection();

    client.send(
        string("Hello there")
    );
    string rec = client.receive();
    cout << rec;


    return 0;
}