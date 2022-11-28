#pragma once

#ifndef SYSTEMS_INFORMATIONS_GPUS_HEADER
#define SYSTEMS_INFORMATIONS_GPUS_HEADER

#include "../../common.hpp"

namespace Systems::Informations::GPUs
{
    class GPU_Information :
        virtual public Systems::Informations::Information_Abstract
    {
        private:

        public:
            GPU_Information(
            ) : Systems::Informations::Information_Abstract()
            {
            }

            ~GPU_Information() = default;
    };
}




#endif