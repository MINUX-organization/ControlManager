#pragma once

#ifndef MANAGERS_FACTORIES_HEADER
#define MANAGERS_FACTORIES_HEADER

#include "common.hpp"

#include "cpus/inc/cpus.hpp"
#include "gpus/inc/gpus.hpp"
#include "motherboards/inc/motherboards.hpp"

namespace Managers::Factories
{
    enum Manager_IDs
    {
        CPUS_MANAGER = 0x00,
        GPUS_MANAGER,
        MOTHERBOARDS_MANAGER
    };

    class Manager_Factory
    {
        private:
            Base::Utilities::Commanders::Commander *m_pCommander;

            Managers::Abstracts::Manager_Abstract *m_pManager;

            Managers::CPUs::CPU *m_pCpu_manager;

            // Managers::GPUs::GPU *m_pGpu_manager;

            Managers::Motherboards::Motherboard *m_pMotherboard_manager;

        public:
            Manager_Factory(
                Base::Utilities::Commanders::Commander *pCommander
            ) : m_pCommander(pCommander)
            {
                m_pCpu_manager = &Managers::CPUs::CPU::get_instance(
                    m_pCommander
                );
                // m_pGpu_manager = &Managers::GPUs::GPU::get_instance(
                //     m_pCommander
                // );
                m_pMotherboard_manager = &Managers::Motherboards::Motherboard::get_instance(
                    m_pCommander
                );
            }

            virtual ~Manager_Factory() = default;

            Managers::Abstracts::Manager_Abstract* get_manager(
                size_t manager_id
            )
            {
                if (manager_id == Managers::Factories::Manager_IDs::CPUS_MANAGER) 
                    return m_pCpu_manager;
                // if (manager_id == Managers::Factories::Manager_IDs::GPUS_MANAGER)
                //     return m_pGpu_manager;
                if (manager_id == Managers::Factories::Manager_IDs::MOTHERBOARDS_MANAGER)
                    return m_pMotherboard_manager;
                return m_pManager;
            }
    };
}

#endif