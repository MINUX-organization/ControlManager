#pragma once

#ifndef SYSTEMS_INFORMATIONS_GPUS_HEADER
#define SYSTEMS_INFORMATIONS_GPUS_HEADER

#include "../../common.hpp"

namespace Systems::Informations::GPUs
{
    class GPU_Information :
        virtual public Systems::Informations::Abstracts::Information_Abstract
    {
        private:
            vector<string> m_filters = {

            };

        public:
            GPU_Information(
            ) : Systems::Informations::Abstracts::Information_Abstract()
            {
            }

            ~GPU_Information() = default;

            void construct(
                vector<string> &raw_informations
            )
            {

            }

            vector<string> get_filters() { return m_filters; }
    };
}




#endif