#pragma once

#ifndef SYSTEMS_INFORMATIONS_FACTORIES_HEADER
#define SYSTEMS_INFORMATIONS_FACTORIES_HEADER

#include "common.hpp"

#include "cpus/inc/cpus.hpp"
#include "gpus/inc/gpus.hpp"
#include "motherboards/inc/motherboards.hpp"

namespace Systems::Informations::Factories
{
    enum Information_IDs
    {
        CPU_INFORMATION = 0x00,
        GPU_INFORMATION,
        MOTHERBOARD_INFORMATION
    };

    class Information_Factory
    {
        private:
            Systems::Informations::Abstracts::Information_Abstract *m_information;

        public:
            Information_Factory() = default;

            virtual ~Information_Factory() = default;

            Systems::Informations::Abstracts::Information_Abstract* get_information(
                size_t information_id
            )
            {
                if (information_id == Systems::Informations::Factories::Information_IDs::CPU_INFORMATION)
                    m_information = new Systems::Informations::CPUs::CPU();
                if (information_id == Systems::Informations::Factories::Information_IDs::MOTHERBOARD_INFORMATION)
                    m_information = new Systems::Informations::Motherboards::Motherboard();
                
                return m_information;
            }

            Systems::Informations::Abstracts::Information_Abstract* get_information(
                size_t information_id,
                size_t gpu_id
            )
            {
                if (information_id == Systems::Informations::Factories::Information_IDs::GPU_INFORMATION)
                    m_information = new Systems::Informations::GPUs::Nvidia(gpu_id);
                
                return m_information;
            }
    };
}

#endif