#pragma once

#ifndef SYSTEMS_INFORMATIONS_COMMON_HEADER
#define SYSTEMS_INFORMATIONS_COMMON_HEADER

#include "../common.hpp"

namespace Systems::Informations
{
    class Information_Abstract
    {
        private:

        protected:
            Kernel::Shells::Executors::Executor m_executor;

            Kernel::Shells::Commands::Command m_command;

            void filter_output(
                string &str, 
                string &filter
            )
            {
                size_t pos = str.find(filter);

                if (pos != string::npos)
                    str.erase(pos, filter.length());
                
                str.erase(
                    0, 
                    str.find_first_not_of(' ')
                );
                str.erase(
                    std::remove(
                        str.begin(),
                        str.end(),
                        '\n'
                    ),
                    str.end()
                );
                str.erase(
                    std::remove(
                        str.begin(),
                        str.end(),
                        '\t'
                    ),
                    str.end()
                );

                if (str[0] == ' ')
                    str.erase(0, 1);
            }

            void construct_information(
                string &information,
                string &filter
            )
            {
                m_command.set_filter(
                    filter
                );
                m_executor.execute(
                    m_command
                );

                information = m_executor.get_result();

                filter_output(
                    information,
                    filter
                );
            }

        public:
            Information_Abstract(
                int command
            ) : m_command(command)
            {
            }

            virtual ~Information_Abstract() = default;
    };
}

#endif