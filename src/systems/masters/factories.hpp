#pragma once

#ifndef SYSTEMS_MASTERS_FACTORIES_HEADER
#define SYSTEMS_MASTERS_FACTORIES_HEADER

#include "common.hpp"

#include "cpus/inc/cpus.hpp"
#include "gpus/inc/gpus.hpp"
#include "motherboards/inc/motherboards.hpp"

namespace Systems::Masters::Factories
{
    enum Master_IDs
    {
        CPU_MASTER = 0x00,
        GPU_MASTER,
        MOTHERBOARD_MASTER
    };

    class Master_Factory
    {
        private:
            Systems::Masters::Abstracts::Master_Abstract *m_master;

        public:
            Master_Factory() = default;

            virtual ~Master_Factory() = default;

            Systems::Masters::Abstracts::Master_Abstract* get_master(
                size_t master_id
            )
            {
                if (master_id == Systems::Masters::Factories::Master_IDs::CPU_MASTER)
                    m_master = new Systems::Masters::CPUs::CPU();
                if (master_id == Systems::Masters::Factories::Master_IDs::MOTHERBOARD_MASTER)
                    m_master = new Systems::Masters::Motherboards::Motherboard();
                
                return m_master;
            }

            Systems::Masters::Abstracts::Master_Abstract* get_master(
                size_t master_id,
                size_t gpu_id,
                Display *display
            )
            {
                if (master_id == Systems::Masters::Factories::GPU_MASTER)
                    m_master = new Systems::Masters::GPUs::Nvidia(
                        gpu_id,
                        display
                    );
                
                return m_master;
            }
    };
}

#endif