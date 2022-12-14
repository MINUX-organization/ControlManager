#pragma once

#ifndef SYSTEMS_INFORMATIONS_COMMON_HEADER
#define SYSTEMS_INFORMATIONS_COMMON_HEADER

#include "../common.hpp"

namespace Systems::Informations::Abstracts
{
    class Information_Abstract
    {
        private:

        protected:
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
            Information_Abstract() = default;

            virtual ~Information_Abstract() = default;

            virtual vector<string> get_filters() = 0; 

            virtual void construct(
                vector<string> &raw_informations
            ) = 0;
    };
}

#endif