#pragma once

#ifndef BASE_GPUS_HEADER
#define BASE_GPUS_HEADER

#include "../../common.hpp"

#include "../../../../systems/informations/gpus/inc/gpus.hpp"
#include "../../../../systems/masters/gpus/inc/gpus.hpp"

namespace Base::Hardwares::GPUs
{
    class Nvidia :
        virtual public Base::Hardwares::Abstracts::Hardware_Abstract
    {
        private:
            Systems::Masters::GPUs::Nvidia m_master;

            Systems::Informations::GPUs::Nvidia m_information;

        public:
            Nvidia(
                size_t gpu_id,
                Display *display,
                Managers::Commanders::Commander *commander
            ) : Base::Hardwares::Abstracts::Hardware_Abstract(),
                m_master(
                    gpu_id,
                    display
                )
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

            json get_full_information()
            {

            }
    };

    class AMD
    {
        private:

        public:

    };
}

#endif