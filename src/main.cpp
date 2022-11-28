#include "main.hpp"

#include "communicators/web_interfaces/inc/web_interfaces.hpp"
#include "kernel/sockets/clients/inc/clients.hpp"

#include "managers/commanders/inc/commanders.hpp"
#include "managers/informations/inc/informations.hpp"

int main(int arc, char* argv[])
{
    ifstream config_file("../config.json");

    json config = json::parse(config_file);
    
    string host = config["web_interface"]["host"];
    int port = config["web_interface"]["port"];

    Managers::Commanders::Commander commander;

    cout << commander.execute_information_command(
        0,
        (string)"Vendor ID:"
    );


    return 0;
}