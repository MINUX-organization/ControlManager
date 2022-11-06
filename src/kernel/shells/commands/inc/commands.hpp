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
        dmidecode_motherboard
    };

    class Command
    {
        private:
            string m_command = "";

            string m_filter = "grep";

            string m_filter_str = "";

            string m_total_command = "";

            map<int, string> m_commands = {
                {0, "lscpu"},
                {1, "ls"},
                {2, "cat"},
                {3, "dmidecode -t 2"}
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

                m_total_command = m_command + " | " + m_filter + ' ' + '\'' + m_filter_str + '\'';
            }

            ~Command() = default;

            string get_command()
            {
                return m_total_command;
            }

            void set_command(int command)
            {
                m_command = m_commands[command];

                m_total_command = m_command;

                if (m_filter != "")
                    m_total_command += " | " + m_filter + ' ' + '\'' + m_filter_str + '\'';
            }

            void set_filter(string &filter)
            {
                m_filter_str = filter;

                m_total_command = m_command + " | " + m_filter + ' ' + '\'' + m_filter_str + '\'';
            }
    };
}





#endif