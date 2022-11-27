/**
 * @file abstracts.hpp
 * @author Daniil Ibragimov (ghaghal93@gmail.com)
 * @brief Contains abstract classes for commands
 * @version 0.1
 * @date 2022-11-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#ifndef SYSTEMS_SHELLS_COMAMNDS_ABSTRACTS_HEADER
#define SYSTEMS_SHELLS_COMAMNDS_ABSTRACTS_HEADER

#include "../../common.hpp"

/**
 * @brief Contains abstract classes for commands
 */
namespace Systems::Shells::Commands::Abstracts
{
    class Command_Information_Abstract
    {
        private:

        protected:
            string m_command = "";

            string m_filter = "grep";

            string m_filter_str = "";

            string m_total_command = "";

        public:
            Command_Information_Abstract(
                const string &command,
                const string &filter
            ) : m_command(command),
                m_filter(filter)
            {
                m_total_command = m_command + " | " + m_filter + " -m 1 " + '\'' + m_filter_str + '\'';
            }

            virtual ~Command_Information_Abstract() = default;

            string get_command()
            {
                return m_total_command;
            }

            void set_command(string &command)
            {
                m_command = command;

                m_total_command = m_command +  " | " + m_filter + " -m 1 " + '\'' + m_filter_str + '\'';
            }

            void set_filter(string &filter)
            {
                m_filter_str = filter;

                m_total_command = m_command + " | " + m_filter + " -m 1 " + '\'' + m_filter_str + '\'';
            }
    };
}

#endif