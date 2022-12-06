/**
 * @file commands.hpp
 * @author Daniil Ibragimov (ghaghal93@gmail.com)
 * @brief Contains list of commands for shell
 * @version 0.1
 * @date 2022-11-10
 * 
 * @copyright Copyright (c) 2022
 */

#pragma once

#ifndef SYSTEMS_SHELL_COMMAND_HEADER
#define SYSTEMS_SHELL_COMMAND_HEADER

#include "abstracts.hpp"

/**
 * @brief Contains classes of commands for shell to get information about something
 */
namespace Systems::Shells::Commands::Informations
{
    class Command_lscpu :
        virtual public Systems::Shells::Commands::Abstracts::Command_Information_Abstract
    {
        private:

        public:
            Command_lscpu(
                const string &filter
            ) : Systems::Shells::Commands::Abstracts::Command_Information_Abstract(
                    "lscpu",
                    filter
                )
            {
            }

            virtual ~Command_lscpu() = default;
    };

    class Command_dmidecode :
        virtual public Systems::Shells::Commands::Abstracts::Command_Information_Abstract
    {
        private:

        public:
            Command_dmidecode(
                const string &filter
            ) : Systems::Shells::Commands::Abstracts::Command_Information_Abstract(
                    "dmidecode -t 2",
                    filter
                )
            {
            }

            virtual ~Command_dmidecode() = default;
    };
}

#endif