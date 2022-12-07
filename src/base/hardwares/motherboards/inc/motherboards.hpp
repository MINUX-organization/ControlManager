#pragma once

#ifndef BASE_MOTHERBOARDS_HEADER
#define BASE_MOTHERBOARDS_HEADER

#include "../../common.hpp"

namespace Base::Hardwares::Motherboards
{
    class Motherboard :
        virtual public Base::Hardwares::Abstracts::Hardware_Abstract
    {
        private:
            Systems::Masters::Motherboards::Motherboard *m_pMaster;

            Systems::Informations::Motherboards::Motherboard *m_pInformation;
        
        public:
            Motherboard(
                Systems::Masters::Motherboards::Motherboard *master,
                Systems::Informations::Motherboards::Motherboard *information
            ) : Base::Hardwares::Abstracts::Hardware_Abstract(),
                m_pMaster(master),
                m_pInformation(information)
            {
            }

            ~Motherboard() = default;

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

                result = {
                    {"information", {
                        {"manufacturer", m_pInformation->get_manufacturer()},
                        {"product-name", m_pInformation->get_product_name()},
                        {"serial-number", m_pInformation->get_serial_number()}
                    }}
                };

                return result;
            }
    };
}

#endif