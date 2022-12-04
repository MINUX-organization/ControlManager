#pragma once

#ifndef BASE_MOTHERBOARDS_HEADER
#define BASE_MOTHERBOARDS_HEADER

#include "../../common.hpp"

#include "../../../../systems/informations/motherboards/inc/motherboards.hpp"
#include "../../../../systems/masters/motherboards/inc/motherboards.hpp"

namespace Base::Hardwares::Motherboards
{
    class Motherboard :
        virtual public Base::Hardwares::Abstracts::Hardware_Abstract
    {
        private:
            Systems::Informations::Motherboards::Motherboard m_information;

            Systems::Masters::Motherboards::Motherboard m_master;
        
        public:
            Motherboard(
                Managers::Commanders::Commander *commander
            ) : Base::Hardwares::Abstracts::Hardware_Abstract()
            {
                vector<string> filters = m_information.get_filters();

                vector<string> raw_information = prepare_information(
                    filters,
                    Systems::Shells::Commands::Commands_Informations::LSCPU,
                    commander
                );

                m_information.construct(
                    raw_information
                );
            }

            ~Motherboard() = default;

            json get_full_information()
            {

            }
    };
}

#endif