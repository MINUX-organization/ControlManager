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
            Base::Hardwares::CPUs::CPU *m_pCpu_hardware;

        protected:
            CPU(
                Base::Utilities::Commanders::Commander *pCommander,
                Base::Hardwares::CPUs::CPU *pCpu_hardware
            ) : Managers::Abstracts::Manager_Abstract(
                    pCommander
                ),
                m_pCpu_hardware(pCpu_hardware)
            {
                vector<string> raw_information;
                vector<string> filters = m_pCpu_hardware->get_information_filters();

                for (auto &filter : filters)
                    raw_information.push_back(
                        m_pCommander->execute_information_command(
                            Systems::Shells::Factories::Command_Information_IDs::LSCPU_COMMAND,
                            filter
                        )
                    );
                
                m_pCpu_hardware->update_full_information(
                    raw_information
                );
            }

        public:
            virtual ~CPU() = default;

            static Managers::CPUs::CPU & get_instance(
                Base::Utilities::Commanders::Commander *pCommander,
                Base::Hardwares::CPUs::CPU *pCpu_hardware
            )
            {
                static Managers::CPUs::CPU instance(
                    pCommander,
                    pCpu_hardware
                );

                return instance;
            }

            json get_full_information()
            {
                return m_pCpu_hardware->get_full_information();
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