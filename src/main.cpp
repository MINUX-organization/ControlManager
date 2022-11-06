#include "main.hpp"

int main(int arc, char* argv[])
{
    Kernel::Shells::Executors::Executor executor;

    Kernel::Shells::Commands::Command lscpu(
        Kernel::Shells::Commands::Commands::lscpu
    );

    Kernel::Shells::Commands::Command lscpu_f(
        Kernel::Shells::Commands::Commands::lscpu,
        static_cast<string>("Architecture")
    );

    cout << lscpu.get_command() << endl;
    cout << lscpu_f.get_command() << endl;

    // executor.execute(lscpu);
    // cout << executor.get_result() << endl;

    executor.execute(lscpu_f);
    cout << executor.get_result() << endl;

    return 0;
}