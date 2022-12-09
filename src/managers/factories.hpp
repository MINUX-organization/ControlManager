#pragma once

#ifndef MANAGERS_FACTORIES_HEADER
#define MANAGERS_FACTORIES_HEADER

#include "common.hpp"

#include "cpus/inc/cpus.hpp"
#include "gpus/inc/gpus.hpp"
#include "motherboards/inc/motherboards.hpp"

#include "../base/hardwares/factories.hpp"

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

            Base::Hardwares::Factories::Hardware_Factory m_hardware_factory;

            Managers::Abstracts::Manager_Abstract *m_pManager;

            Managers::CPUs::CPU *m_pCpu_manager;

            Managers::GPUs::GPU *m_pGpu_manager;

            Managers::Motherboards::Motherboard *m_pMotherboard_manager;

            vector<Base::Hardwares::GPUs::Nvidia*> prepare_nvidia_gpus()
            {
                bool error;

                int nvidia_gpus_count = 0;

                vector<Base::Hardwares::GPUs::Nvidia*> nvidia_gpus;

                Display *pDisplay = XOpenDisplay(nullptr);

                if (pDisplay == nullptr)
                    throw Kernel::Exceptions::Managers::Factories::Error_Open_Display(
                        pDisplay
                    );

                // Initialize all Nvidia GPUs
                error = XNVCTRLQueryTargetCount(
                    pDisplay,
                    NV_CTRL_TARGET_TYPE_GPU,
                    &nvidia_gpus_count
                );
                
                if (!error)
                    throw Kernel::Exceptions::Managers::Factories::Error_Query_Nvidia_Amount(
                        pDisplay
                    );

                for (int i = 0; i < nvidia_gpus_count; i++)
                    m_hardware_factory.get_hardware(
                        Base::Hardwares::Factories::Hardware_IDs::GPU_HARDWARE,
                        i,
                        pDisplay
                    );
                
                return nvidia_gpus;
            }

            vector<Base::Hardwares::GPUs::AMD*> prepare_amd_gpus()
            {
                vector<Base::Hardwares::GPUs::AMD*> amd_gpus;
                
                return amd_gpus;
            }

        public:
            Manager_Factory(
                Base::Utilities::Commanders::Commander *pCommander
            ) : m_pCommander(pCommander)
            {
                vector<Base::Hardwares::GPUs::Nvidia*> nvidia_gpus = prepare_nvidia_gpus();
                vector<Base::Hardwares::GPUs::AMD*> amd_gpus = prepare_amd_gpus();

                Base::Hardwares::CPUs::CPU *pCpu_hardware = dynamic_cast<Base::Hardwares::CPUs::CPU*>(
                    m_hardware_factory.get_hardware(
                        Base::Hardwares::Factories::Hardware_IDs::CPU_HARDWARE
                    )
                );
                Base::Hardwares::Motherboards::Motherboard *pMotherboard_hardware = dynamic_cast<Base::Hardwares::Motherboards::Motherboard*>(
                    m_hardware_factory.get_hardware(
                        Base::Hardwares::Factories::Hardware_IDs::MOTHERBOARD_HARDWARE
                    )
                );

                m_pCpu_manager = &Managers::CPUs::CPU::get_instance(
                    m_pCommander,
                    pCpu_hardware
                );
                // m_pGpu_manager = &Managers::GPUs::GPU::get_instance(
                //     m_pCommander,
                //     nvidia_gpus,
                //     amd_gpus
                // );
                m_pMotherboard_manager = &Managers::Motherboards::Motherboard::get_instance(
                    m_pCommander,
                    pMotherboard_hardware
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