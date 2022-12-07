#pragma once

#ifndef BASE_HARDWARES_FACTORIES_HEADER
#define BASE_HARDWARES_FACTORIES_HEADER

#include "common.hpp"

#include "cpus/inc/cpus.hpp"
#include "gpus/inc/gpus.hpp"
#include "motherboards/inc/motherboards.hpp"

namespace Base::Hardwares::Factories
{
    enum Hardware_IDs
    {
        CPU_HARDWARE = 0x00,
        GPU_HARDWARE,
        MOTHERBOARD_HARDWARE
    };

    class Hardware_Factory
    {
        private:
            Base::Hardwares::Abstracts::Hardware_Abstract *m_hardware;

            Systems::Masters::Factories::Master_Factory m_master_factory;

            Systems::Informations::Factories::Information_Factory m_information_factory;

        public:
            Hardware_Factory() = default;

            virtual ~Hardware_Factory() = default;

            Base::Hardwares::Abstracts::Hardware_Abstract* get_hardware(
                size_t hardware_id
            )
            {
                if (hardware_id == Base::Hardwares::Factories::Hardware_IDs::CPU_HARDWARE)
                {
                    Systems::Masters::CPUs::CPU *cpu_master = dynamic_cast<Systems::Masters::CPUs::CPU*>(
                        m_master_factory.get_master(
                            Systems::Masters::Factories::Master_IDs::CPU_MASTER
                        )
                    );
                    Systems::Informations::CPUs::CPU *cpu_information = dynamic_cast<Systems::Informations::CPUs::CPU*>(
                        m_information_factory.get_information(
                            Systems::Informations::Factories::Information_IDs::CPU_INFORMATION
                        )
                    );
                    m_hardware = new Base::Hardwares::CPUs::CPU(
                        cpu_master,
                        cpu_information
                    );
                }
                if (hardware_id == Base::Hardwares::Factories::Hardware_IDs::MOTHERBOARD_HARDWARE)
                {
                    Systems::Masters::Motherboards::Motherboard *motherboard_master = dynamic_cast<Systems::Masters::Motherboards::Motherboard*>(
                        m_master_factory.get_master(
                            Systems::Masters::Factories::Master_IDs::MOTHERBOARD_MASTER
                        )
                    );
                    Systems::Informations::Motherboards::Motherboard *motherboard_information = dynamic_cast<Systems::Informations::Motherboards::Motherboard*>(
                        m_information_factory.get_information(
                            Systems::Informations::Factories::Information_IDs::MOTHERBOARD_INFORMATION
                        )
                    );
                    m_hardware = new Base::Hardwares::Motherboards::Motherboard(
                        motherboard_master,
                        motherboard_information
                    );
                }
                
                return m_hardware;
            }

            Base::Hardwares::Abstracts::Hardware_Abstract* get_hardware(
                size_t hardware_id,
                size_t gpu_id,
                Display *display
            )
            {
                if (hardware_id == Base::Hardwares::Factories::Hardware_IDs::GPU_HARDWARE)
                {
                    Systems::Masters::GPUs::Nvidia *nvidia_master = dynamic_cast<Systems::Masters::GPUs::Nvidia*>(
                        m_master_factory.get_master(
                            Systems::Masters::Factories::Master_IDs::GPU_MASTER,
                            gpu_id,
                            display
                        )
                    );
                    Systems::Informations::GPUs::Nvidia *nvidia_information = dynamic_cast<Systems::Informations::GPUs::Nvidia*>(
                        m_information_factory.get_information(
                            Systems::Informations::Factories::Information_IDs::GPU_INFORMATION,
                            gpu_id
                        )
                    );
                    m_hardware = new Base::Hardwares::GPUs::Nvidia(
                        nvidia_master,
                        nvidia_information
                    );
                }
                
                return m_hardware;
            }
    };
}

#endif