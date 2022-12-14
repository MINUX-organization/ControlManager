#pragma once

#ifndef BASE_HARDWARES_COMMON_HEADER
#define BASE_HARDWARES_COMMON_HEADER

#include "../common.hpp"

#include "../utilities/commanders/inc/commanders.hpp"

#include "../../systems/masters/factories.hpp"
#include "../../systems/informations/factories.hpp"

namespace Base::Hardwares::Abstracts
{
    class Hardware_Abstract
    {
        private:

        protected:
            vector<string> prepare_information(
                vector<string> &filters,
                size_t command,
                Base::Utilities::Commanders::Commander *commander
            )
            {
                vector<string> results;

                for (auto& filter : filters)
                    results.push_back(
                        commander->execute_information_command(
                            command,
                            filter
                        )
                    );
                
                return results;
            }

        public:
            Hardware_Abstract() = default;

            virtual ~Hardware_Abstract() = default;

            virtual void update_full_information(
                vector<string> &raw_information
            ) = 0;

            virtual vector<string> get_information_filters() = 0;

            virtual json get_full_information() = 0;
    };
}

#endif