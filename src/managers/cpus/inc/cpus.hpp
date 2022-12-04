#pragma once

#ifndef MANAGERS_CPUS_HEADER
#define MANAGERS_CPUS_HEADER

#include "../../common.hpp"

namespace Managers::CPUs
{
    class CPU :
        virtual public Managers::Abstracts::Manager_Abstract
    {
        private:

        protected:
            CPU(
            ) : Managers::Abstracts::Manager_Abstract()
            {
            }

        public:
            virtual ~CPU() = default;

            static Managers::CPUs::CPU & get_instance()
            {
                static Managers::CPUs::CPU instance;

                return instance;
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