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
    Managers::Informations::Information_Manager information_manager(
        &commander
    );

    information_manager.get_cpu_information();

    return 0;
}