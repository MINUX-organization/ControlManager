#pragma once

#ifndef BASE_MOTHERBOARDS_HEADER
#define BASE_MOTHERBOARDS_HEADER

#include "../../common.hpp"

#include "../../../../systems/informations/motherboards/inc/motherboards.hpp"
#include "../../../../systems/masters/motherboards/inc/motherboards.hpp"

namespace Base::Hardwares::Motherboards
{
    class Motherboard :
        virtual public Base::Hardwares::Abstracts::Hardware_Abstract
    {
        private:
            Systems::Informations::Motherboards::Motherboard m_information;

            Systems::Masters::Motherboards::Motherboard m_master;
        
        public:
            Motherboard() : Base::Hardwares::Abstracts::Hardware_Abstract()
            {
            }

            ~Motherboard() = default;

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

                result = {
                    {"information", {
                        {"manufacturer", m_information.get_manufacturer()},
                        {"product-name", m_information.get_product_name()},
                        {"serial-number", m_information.get_serial_number()}
                    }}
                };

                return result;
            }
    };
}

#endif