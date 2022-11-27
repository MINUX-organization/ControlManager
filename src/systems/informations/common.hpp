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
            string m_raw_information;

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

        public:
            Information_Abstract(
                string &raw_information
            ) : m_raw_information(
                    raw_information
                )
            {
            }

            virtual ~Information_Abstract() = default;

            string construct_information(
                string &filter
            )
            {
                filter_output(
                    m_raw_information,
                    filter
                );

                return m_raw_information;
            }
    };
}

#endif