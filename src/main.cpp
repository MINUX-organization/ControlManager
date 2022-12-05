#include "main.hpp"

#include "communicators/web_interfaces/inc/web_interfaces.hpp"
#include "kernel/sockets/clients/inc/clients.hpp"

#include "managers/cpus/inc/cpus.hpp"
#include "managers/gpus/inc/gpus.hpp"
#include "managers/motherboards/inc/motherboards.hpp"

int main(int arc, char* argv[])
{
    ifstream config_file("../config.json");

    json config = json::parse(config_file);
    
    string host = config["web_interface"]["host"];
    int port = config["web_interface"]["port"];


    Base::Utilities::Commanders::Commander &commander = Base::Utilities::Commanders::Commander::get_instance();

    Managers::CPUs::CPU &cpu_mngr = Managers::CPUs::CPU::get_instance(
        &commander
    );

    json result = cpu_mngr.get_full_information();

    cout << result << endl;

    return 0;
}