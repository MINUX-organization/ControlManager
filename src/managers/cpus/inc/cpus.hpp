#pragma once

#ifndef MANAGERS_CPUS_HEADER
#define MANAGERS_CPUS_HEADER

#include "../../common.hpp"

#include "../../../base/hardwares/cpus/inc/cpus.hpp"

namespace Managers::CPUs
{
    class CPU :
        virtual public Managers::Abstracts::Manager_Abstract
    {
        private:
            Base::Hardwares::CPUs::CPU m_cpu_hardware;

        protected:
            CPU(
                Base::Utilities::Commanders::Commander *pCommander
            ) : Managers::Abstracts::Manager_Abstract(
                    pCommander
                )
            {
                vector<string> raw_information;
                vector<string> filters = m_cpu_hardware.get_information_filters();

                for (auto &filter : filters)
                    raw_information.push_back(
                        m_pCommander->execute_information_command(
                            Systems::Shells::Factories::Command_Information_IDs::LSCPU,
                            filter
                        )
                    );
                
                m_cpu_hardware.update_full_information(
                    raw_information
                );
            }

        public:
            virtual ~CPU() = default;

            static Managers::CPUs::CPU & get_instance(
                Base::Utilities::Commanders::Commander *pCommander
            )
            {
                static Managers::CPUs::CPU instance(
                    pCommander
                );

                return instance;
            }

            json get_full_information()
            {
                return m_cpu_hardware.get_full_information();
            }

            CPU(
                const Managers::CPUs::CPU&
            ) = delete;

            CPU(
                Managers::CPUs::CPU&&
            ) = delete;

            Managers::CPUs::CPU operator = (
                const Managers::CPUs::CPU&
            ) = delete;

            Managers::CPUs::CPU operator = (
                Managers::CPUs::CPU&&
            ) = delete;
    };
}

#endif