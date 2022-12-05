#pragma once

#ifndef BASE_GPUS_HEADER
#define BASE_GPUS_HEADER

#include "../../common.hpp"

#include "../../../../systems/informations/gpus/inc/gpus.hpp"
#include "../../../../systems/masters/gpus/inc/gpus.hpp"

namespace Base::Hardwares::GPUs
{
    class Nvidia :
        virtual public Base::Hardwares::Abstracts::Hardware_Abstract
    {
        private:
            Systems::Masters::GPUs::Nvidia m_master;

            Systems::Informations::GPUs::Nvidia m_information;

        public:
            Nvidia(
                size_t gpu_id,
                Display *display
            ) : Base::Hardwares::Abstracts::Hardware_Abstract(),
                m_master(
                    gpu_id,
                    display
                )
            {
            }

            void update_full_information(
                vector<string> &raw_information
            )
            {
                m_information.construct(
                    raw_information
                );
            }

            vector<string> get_information_filters()
            {
                return m_information.get_filters();
            }

            json get_full_information()
            {
                json result = {};

                return result;
            }
    };

    class AMD
    {
        private:

        public:

    };
}

#endif