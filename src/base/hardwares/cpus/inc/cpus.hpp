#pragma once

#ifndef BASE_CPUS_HEADER
#define BASE_CPUS_HEADER

#include "../../common.hpp"

#include "../../../../systems/informations/cpus/inc/cpus.hpp"
#include "../../../../systems/masters/cpus/inc/cpus.hpp"

namespace Base::Hardwares::CPUs
{
    class CPU : 
        virtual public Base::Hardwares::Abstracts::Hardware_Abstract
    {
        private:
            Systems::Masters::CPUs::CPU m_master;

            Systems::Informations::CPUs::CPU m_information;

        public:
            CPU(
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

            ~CPU() = default;

            json get_full_information()
            {
                json result = {};

                return result;
            }
    };
}

#endif