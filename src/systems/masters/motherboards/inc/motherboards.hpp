#pragma once

#ifndef SYSTEMS_MASTERS_MOTHERBOARDS_HEADER
#define SYSTEMS_MASTERS_MOTHERBOARDS_HEADER

#include "../../common.hpp"

namespace Systems::Masters::Motherboards
{
    class Motherboard :
        virtual public Systems::Masters::Abstracts::Master_Abstract
    {
        private:

        public:
            Motherboard() : Systems::Masters::Abstracts::Master_Abstract()
            {
            }

            virtual ~Motherboard() = default;
    };
}

#endif