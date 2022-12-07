#include "main.hpp"

#include "communicators/web_interfaces/inc/web_interfaces.hpp"
#include "kernel/sockets/clients/inc/clients.hpp"

#include "managers/factories.hpp"

int main(int arc, char* argv[])
{
    ifstream config_file("../config.json");

    json config = json::parse(config_file);
    
    string host = config["web_interface"]["host"];
    int port = config["web_interface"]["port"];


    Base::Utilities::Commanders::Commander &commander = Base::Utilities::Commanders::Commander::get_instance();

    Managers::Factories::Manager_Factory mngr_fctr(
        &commander
    );

    Managers::CPUs::CPU* cpu_mngr = dynamic_cast<Managers::CPUs::CPU*>(
        mngr_fctr.get_manager(
            Managers::Factories::Manager_IDs::CPUS_MANAGER
        )
    );
    Managers::Motherboards::Motherboard* motherboard_mngr = dynamic_cast<Managers::Motherboards::Motherboard*>(
        mngr_fctr.get_manager(
            Managers::Factories::Manager_IDs::MOTHERBOARDS_MANAGER
        )
    );

    cout << cpu_mngr->get_full_information() << endl;
    cout << motherboard_mngr->get_full_information() << endl;

    return 0;
}