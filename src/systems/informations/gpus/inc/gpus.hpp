#pragma once

#ifndef SYSTEMS_INFORMATIONS_GPUS_HEADER
#define SYSTEMS_INFORMATIONS_GPUS_HEADER

#include "../../common.hpp"

namespace Systems::Informations::GPUs
{
    class Nvidia :
        virtual public Systems::Informations::Abstracts::Information_Abstract
    {
        private:
            size_t m_gpu_id;

            vector<string> m_filters = {

            };

        public:
            Nvidia(
                size_t gpu_id
            ) : Systems::Informations::Abstracts::Information_Abstract(),
                m_gpu_id(gpu_id)
            {
            }

            virtual ~Nvidia() = default;

            void construct(
                vector<string> &raw_informations
            )
            {

            }

            vector<string> get_filters() { return m_filters; }
    };

    class AMD :
        virtual public Systems::Informations::Abstracts::Information_Abstract
    {
        private:
            vector<string> m_filters = {

            };

        public:
            AMD(
            ) : Systems::Informations::Abstracts::Information_Abstract()
            {
            }
        
            virtual ~AMD() = default;

            void construct(
                vector<string> &raw_informations
            )
            {

            }

            vector<string> get_filters() { return m_filters; }
    };
}




#endif