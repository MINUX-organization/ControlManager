#pragma once

#ifndef MANAGERS_COMMANDERS_HEADER
#define MANAGERS_COMMANDERS_HEADER

#include "../../common.hpp"

#include "../../../../systems/shells/executors/inc/executors.hpp"

namespace Base::Utilities::Commanders
{
    class Commander
    {
        private:
            Systems::Shells::Executors::Executor m_executor;

            Systems::Shells::Commands::Command_Factory m_command_factory;

        protected:
            Commander() = default;

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

            static Base::Utilities::Commanders::Commander & get_instance()
            {
                static Base::Utilities::Commanders::Commander instance;

                return instance;
            }

            Commander(
                const Base::Utilities::Commanders::Commander&
            ) = delete;

            Commander(
                Base::Utilities::Commanders::Commander&&
            ) = delete;

            Base::Utilities::Commanders::Commander operator = (
                const Base::Utilities::Commanders::Commander&
            ) = delete;

            Base::Utilities::Commanders::Commander operator = (
                Base::Utilities::Commanders::Commander&&
            ) = delete;
    };
}

#endif