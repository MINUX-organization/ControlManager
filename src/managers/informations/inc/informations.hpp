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
            boost::signals2::signal<string (
                size_t,
                string
            )> m_signal_commander;

            Systems::Informations::CPUs::CPU_Information m_cpu_info;

            Systems::Informations::GPUs::GPU_Information m_gpu_info;

            Systems::Informations::Motherboards::Motherboard_Information m_motherboard_info;

            vector<string> setup_raw_information(
                vector<string> &filters,
                size_t command
            )
            {
                vector<string> results;

                for (auto& filter : filters)
                    results.push_back(
                        *m_signal_commander(
                            command,
                            filter
                        )
                    );
                
                return results;
            }

        public:
            Information_Manager(
                Managers::Commanders::Commander *commander
            )
            {
                m_signal_commander.connect(
                    boost::bind(
                        &Managers::Commanders::Commander::execute_information_command,
                        commander,
                        boost::placeholders::_1,
                        boost::placeholders::_2
                    )
                );
            }

            virtual ~Information_Manager() = default;

            void get_cpu_information()
            {
                vector<string> filters = m_cpu_info.get_filters();

                vector<string> raw_information = setup_raw_information(
                    filters,
                    Systems::Shells::Commands::Commands_Informations::LSCPU
                );

                m_cpu_info.construct(
                    raw_information
                );
            }

            void get_motherboard_information()
            {
                vector<string> filters = m_motherboard_info.get_filters();

                vector<string> raw_information = setup_raw_information(
                    filters,
                    Systems::Shells::Commands::Commands_Informations::DMIDECODE
                );

                m_motherboard_info.construct(
                    raw_information
                );
            }
    };
}

#endif