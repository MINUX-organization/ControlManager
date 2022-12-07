#pragma once

#ifndef BASE_GPUS_HEADER
#define BASE_GPUS_HEADER

#include "../../common.hpp"

namespace Base::Hardwares::GPUs
{
    class Nvidia :
        virtual public Base::Hardwares::Abstracts::Hardware_Abstract
    {
        private:
            Systems::Masters::GPUs::Nvidia *m_pMaster;

            Systems::Informations::GPUs::Nvidia *m_pInformation;

        public:
            Nvidia(
                Systems::Masters::GPUs::Nvidia *master,
                Systems::Informations::GPUs::Nvidia *information
            ) : Base::Hardwares::Abstracts::Hardware_Abstract(),
                m_pMaster(master),
                m_pInformation(information)
            {
            }

            void update_full_information(
                vector<string> &raw_information
            )
            {
                m_pInformation->construct(
                    raw_information
                );
            }

            vector<string> get_information_filters()
            {
                return m_pInformation->get_filters();
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