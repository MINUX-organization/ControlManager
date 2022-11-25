#include "main.hpp"

#include "communicators/web_interfaces/inc/web_interfaces.hpp"

int main(int arc, char* argv[])
{
    ifstream config_file("../config.json");

    json config = json::parse(config_file);
    
    string host = config["web_interface"]["host"];
    string port = config["web_interface"]["port"];

    return 0;
}