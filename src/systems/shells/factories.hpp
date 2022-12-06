#pragma once

#ifndef SYSTEMS_SHELLS_FACTORIES_HEADER
#define SYSTEMS_SHELLS_FACTORIES_HEADER

#include "common.hpp"

#include "commands/inc/commands.hpp"
#include "executors/inc/executors.hpp"

namespace Systems::Shells::Factories
{
    enum Command_Information_IDs
    {
        LSCPU = 0x00,
        DMIDECODE
    };

    class Command_Factory
    {
        private:
            Systems::Shells::Commands::Abstracts::Command_Information_Abstract *m_command;

        public:
            Command_Factory() = default;

            virtual ~Command_Factory() = default;

            Systems::Shells::Commands::Abstracts::Command_Information_Abstract get_command(
                size_t command,
                string &filter
            )
            {
                if (command == Systems::Shells::Factories::Command_Information_IDs::LSCPU)
                    m_command = new Systems::Shells::Commands::Informations::Command_lscpu(
                        filter
                    );
                if (command == Systems::Shells::Factories::Command_Information_IDs::DMIDECODE)
                    m_command = new Systems::Shells::Commands::Informations::Command_dmidecode(
                        filter
                    );
                
                return *m_command;
            }
    };
}

#endif