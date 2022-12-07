#pragma once

#ifndef MANAGERS_MOTHERBOARDS_HEADER
#define MANAGERS_MOTHERBOARDS_HEADER

#include "../../common.hpp"

#include "../../../base/hardwares/motherboards/inc/motherboards.hpp"

namespace Managers::Motherboards
{
    class Motherboard :
        virtual public Managers::Abstracts::Manager_Abstract
    {
        private:
            Base::Hardwares::Motherboards::Motherboard *m_pMotherboard_hardware;

        protected:
            Motherboard(
                Base::Utilities::Commanders::Commander *pCommander,
                Base::Hardwares::Motherboards::Motherboard *pMotherboard_hardware
            ) : Managers::Abstracts::Manager_Abstract(
                    pCommander
                ),
                m_pMotherboard_hardware(pMotherboard_hardware)
            {
                vector<string> raw_information;
                vector<string> filters = m_pMotherboard_hardware->get_information_filters();

                for (auto &filter : filters)
                    raw_information.push_back(
                        m_pCommander->execute_information_command(
                            Systems::Shells::Factories::Command_Information_IDs::DMIDECODE_COMMAND,
                            filter
                        )
                    );
                
                m_pMotherboard_hardware->update_full_information(
                    raw_information
                );
            }

        public:
            virtual ~Motherboard() = default;

            static Managers::Motherboards::Motherboard & get_instance(
                Base::Utilities::Commanders::Commander *pCommander,
                Base::Hardwares::Motherboards::Motherboard *pMotherboard_hardware
            )
            {
                static Managers::Motherboards::Motherboard instance(
                    pCommander,
                    pMotherboard_hardware
                );

                return instance;
            }

            json get_full_information()
            {
                return m_pMotherboard_hardware->get_full_information();
            }

            Motherboard(
                const Managers::Motherboards::Motherboard&
            ) = delete;

            Motherboard(
                Managers::Motherboards::Motherboard&&
            ) = delete;

            Managers::Motherboards::Motherboard operator = (
                const Managers::Motherboards::Motherboard&
            ) = delete;

            Managers::Motherboards::Motherboard operator = (
                Managers::Motherboards::Motherboard&&
            ) = delete;
    };
}

#endif