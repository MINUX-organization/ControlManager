#pragma once

#ifndef SYSTEMS_INFORMATIONS_MOTHERBOARDS_HEADER
#define SYSTEMS_INFORMATIONS_MOTHERBOARDS_HEADER

#include "../../common.hpp"

namespace Systems::Informations::Motherboards
{
    class Motherboard_Information :
        virtual public Systems::Informations::Information_Abstract
    {
        private:
            string m_serial_number = "";

            string m_manufacturer = "";

            string m_product_name = "";

            array<string, 3> m_filters = {
                "Serial Number:",
                "Manufacturer:",
                "Product Name:"
            };

        public:
            Motherboard_Information(
            ) : Systems::Informations::Information_Abstract()
            {
                m_serial_number = construct_information(
                    m_filters[0]
                );
                m_manufacturer = construct_information(
                    m_filters[1]
                );
                m_product_name = construct_information(
                    m_filters[2]
                );
            }

            ~Motherboard_Information() = default;

            string get_serial_number() { return m_serial_number; }

            string get_product_name() { return m_product_name; }

            string get_manufacturer() { return m_manufacturer; }
    };
}

#endif