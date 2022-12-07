#pragma once

#ifndef SYSTEMS_MASTERS_CPUS_HEADER
#define SYSTEMS_MASTERS_CPUS_HEADER

#include "../../common.hpp"

namespace Systems::Masters::CPUs
{
    class CPU :
        virtual public Systems::Masters::Abstracts::Master_Abstract
    {
        private:

        public:
            CPU() : Systems::Masters::Abstracts::Master_Abstract()
            {
            }

            virtual ~CPU() = default;
    };
}

#endif