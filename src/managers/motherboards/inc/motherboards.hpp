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
            Base::Hardwares::Motherboards::Motherboard m_motherboard_hardware;

        protected:
            Motherboard(
                Base::Utilities::Commanders::Commander *pCommander
            ) : Managers::Abstracts::Manager_Abstract(
                    pCommander
                )
            {
                vector<string> raw_information;
                vector<string> filters = m_motherboard_hardware.get_information_filters();

                for (auto &filter : filters)
                    raw_information.push_back(
                        m_pCommander->execute_information_command(
                            Systems::Shells::Commands::Commands_Informations::LSCPU,
                            filter
                        )
                    );
                
                m_motherboard_hardware.update_full_information(
                    raw_information
                );
            }

        public:
            virtual ~Motherboard() = default;

            static Managers::Motherboards::Motherboard & get_instance(
                Base::Utilities::Commanders::Commander *pCommander
            )
            {
                static Managers::Motherboards::Motherboard instance(
                    pCommander
                );

                return instance;
            }

            json get_full_information()
            {
                return m_motherboard_hardware.get_full_information();
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