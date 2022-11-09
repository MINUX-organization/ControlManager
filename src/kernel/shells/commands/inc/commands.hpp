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

#ifndef KERNEL_SHELL_COMMAND_HEADER
#define KERNEL_SHELL_COMMAND_HEADER

#include "abstracts.hpp"

/**
 * @brief Contains classes of commands for shell
 */
namespace Kernel::Shells::Commands
{
    /**
     * @brief Enumeration of commands
     */
    enum Commands
    {
        /**
         * @brief lscpu
         */
        lscpu = 0x00,

        /**
         * @brief ls
         */
        ls,

        /**
         * @brief cat
         */
        cat,

        /**
         * @brief dmidecode -t 2
         */
        dmidecode_motherboard
    };

    /**
     * @brief Command object
     */
    class Command
    {
        private:
            /**
             * @brief Command string
             */
            string m_command = "";

            /**
             * @brief Filter for command
             */
            string m_filter = "grep";

            /**
             * @brief Fitler string for command
             */
            string m_filter_str = "";

            /**
             * @brief Full command with filter
             */
            string m_total_command = "";

            /**
             * @brief Map of commands
             */
            map<int, string> m_commands = {
                {0, "lscpu"},
                {1, "ls"},
                {2, "cat"},
                {3, "dmidecode -t 2"}
            };

        public:
            /**
             * @brief Construct a new Command object
             * 
             * @param command Command ID
             */
            Command(
                int command
            )
            {
                m_command = m_commands[command];
            }

            /**
             * @brief Construct a new Command object
             * 
             * @param command Command ID
             * @param filter Filter string for command
             */
            Command(
                int command,
                const string &filter
            ) : m_filter_str(filter)
            {
                m_command = m_commands[command];

                m_total_command = m_command + " | " + m_filter + " -m 1 " + '\'' + m_filter_str + '\'';
            }

            /**
             * @brief Destroy the Command object
             */
            ~Command() = default;

            /**
             * @brief Get the command object
             * 
             * @return string 
             */
            string get_command()
            {
                return m_total_command;
            }

            /**
             * @brief Set the command object
             * 
             * @param command Set command by ID
             */
            void set_command(int command)
            {
                m_command = m_commands[command];

                m_total_command = m_command;

                if (m_filter != "")
                    m_total_command += " | " + m_filter + " -m 1 " + '\'' + m_filter_str + '\'';
            }

            /**
             * @brief Set the filter object
             * 
             * @param filter Set filter string
             */
            void set_filter(string &filter)
            {
                m_filter_str = filter;

                m_total_command = m_command + " | " + m_filter + " -m 1 " + '\'' + m_filter_str + '\'';
            }
    };
}





#endif