#pragma once

#ifndef MANAGERS_INFORMATIONS_HEADER
#define MANAGERS_INFORMATIONS_HEADER

#include "../../common.hpp"

#include "../../commanders/inc/commanders.hpp"

#include "../../../systems/informations/cpus/inc/cpus.hpp"
#include "../../../systems/informations/gpus/inc/gpus.hpp"
#include "../../../systems/informations/motherboards/inc/motherboards.hpp"

namespace Managers::Informations
{
    class Information_Manager
    {
        private:
            boost::signals2<string (
                size_t,
                string
            )> m_signal_commander;

            Systems::Informations::CPUs::CPU_Information *m_cpu_info;

            Systems::Informations::GPUs::GPU_Information *m_gpu_info;

            Systems::Informations::Motherboards::Motherboard_Information *m_motherboard_info;

        public:
            Information_Manager(
                Managers::Commanders::Commander *commander
            )
            {
                m_signal_commander.connect(
                    boost::bind(
                        &Managers::Commanders::Commander::execute_information_command,
                        command,
                        _1,
                        _2                    
                    )
                );
            }

            virtual ~Information_Manager() = default;

            void get_cpu_information()
            {
                string information = 
            }
    };
}

#endif