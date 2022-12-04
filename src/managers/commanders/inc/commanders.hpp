#pragma once

#ifndef MANAGERS_COMMANDERS_HEADER
#define MANAGERS_COMMANDERS_HEADER

#include "../../common.hpp"

#include "../../../systems/shells/executors/inc/executors.hpp"

namespace Managers::Commanders
{
    class Commander :
        virtual public Managers::Abstracts::Manager_Abstract
    {
        private:
            Systems::Shells::Executors::Executor m_executor;

            Systems::Shells::Commands::Command_Factory m_command_factory;

        protected:
            Commander(
            ) : Managers::Abstracts::Manager_Abstract()
            {
            }

        public:
            virtual ~Commander() = default;

            string execute_information_command(
                size_t command_id,
                string filter
            )
            {
                Systems::Shells::Commands::Abstracts::Command_Information_Abstract command = m_command_factory.get_command(
                    command_id,
                    filter
                );

                m_executor.execute(
                    command
                );

                return m_executor.get_result();
            }

            static Managers::Commanders::Commander & get_instance()
            {
                static Managers::Commanders::Commander instance;

                return instance;
            }

            Commander(
                const Managers::Commanders::Commander&
            ) = delete;

            Commander(
                Managers::Commanders::Commander&&
            ) = delete;

            Managers::Commanders::Commander operator = (
                const Managers::Commanders::Commander&
            ) = delete;

            Managers::Commanders::Commander operator = (
                Managers::Commanders::Commander&&
            ) = delete;
    };
}

#endif