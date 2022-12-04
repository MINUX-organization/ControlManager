#pragma once

#ifndef SYSTEMS_INFORMATIONS_MOTHERBOARDS_HEADER
#define SYSTEMS_INFORMATIONS_MOTHERBOARDS_HEADER

#include "../../common.hpp"

namespace Systems::Informations::Motherboards
{
    class Motherboard :
        virtual public Systems::Informations::Abstracts::Information_Abstract
    {
        private:
            string m_serial_number = "";

            string m_manufacturer = "";

            string m_product_name = "";

            vector<string> m_filters = {
                "Serial Number:",
                "Manufacturer:",
                "Product Name:"
            };

        public:
            Motherboard(
            ) : Systems::Informations::Abstracts::Information_Abstract()
            {
            }

            ~Motherboard() = default;

            void construct(
                vector<string> &raw_informations
            )
            {
                for (size_t i = 0; i < raw_informations.size(); i++)
                    filter_output(
                        raw_informations[i],
                        m_filters[i]
                    );
                
                m_serial_number = raw_informations[0];
                m_manufacturer = raw_informations[1];
                m_product_name = raw_informations[2];
            }

            vector<string> get_filters() { return m_filters; }

            string get_serial_number() { return m_serial_number; }

            string get_product_name() { return m_product_name; }

            string get_manufacturer() { return m_manufacturer; }
    };
}

#endif