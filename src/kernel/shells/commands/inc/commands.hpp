#pragma once

#ifndef KERNEL_SHELL_COMMAND_HEADER
#define KERNEL_SHELL_COMMAND_HEADER

#include "abstracts.hpp"

namespace Kernel::Shells::Commands
{
    enum Commands
    {
        lscpu = 0x00,
        ls,
        cat,
    };

    class Command
    {
        private:
            string m_command = "";

            string m_filter = "grep";

            string m_filter_str = "";

            map<int, string> m_commands = {
                {0, "lscpu"},
                {1, "ls"},
                {2, "cat"}
            };

        public:
            Command(
                int command
            )
            {
                m_command = m_commands[command];
            }

            Command(
                int command,
                const string &filter
            ) : m_filter_str(filter)
            {
                m_command = m_commands[command];

                m_command += " | " + m_filter + ' ' + '\'' + m_filter_str + '\'';
            }

            ~Command() = default;

            string get_command()
            {
                return m_command;
            }
    };
}





#endif