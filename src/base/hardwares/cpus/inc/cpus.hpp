#pragma once

#ifndef BASE_CPUS_HEADER
#define BASE_CPUS_HEADER

#include "../../common.hpp"

namespace Base::Hardwares::CPUs
{
    class CPU : 
        virtual public Base::Hardwares::Abstracts::Hardware_Abstract
    {
        private:
            Systems::Masters::CPUs::CPU *m_pMaster;

            Systems::Informations::CPUs::CPU *m_pInformation;

        public:
            CPU(
                Systems::Masters::CPUs::CPU *master,
                Systems::Informations::CPUs::CPU *information
            ) : Base::Hardwares::Abstracts::Hardware_Abstract(),
                m_pMaster(master),
                m_pInformation(information)
            {
            }

            ~CPU() = default;

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
                        {"model-name", m_pInformation->get_model_name()},
                        {"architecture", m_pInformation->get_architecture()},
                        {"op-modes", m_pInformation->get_op_mode()},
                        {"cores", {
                            {"cpus", m_pInformation->get_cpus()},
                            {"threads-per-core", m_pInformation->get_threads_per_core()},
                            {"threads-per-socket", m_pInformation->get_threads_per_socket()},
                            {"sockets", m_pInformation->get_sockets()}
                        }}
                    }},
                    {"state", {
                        {"clocks-mhz", {
                            {"scalling", m_pInformation->get_clock_scaling()},
                            {"max", m_pInformation->get_clock_max()},
                            {"min", m_pInformation->get_clock_min()}
                        }}
                    }}
                };

                return result;
            }
    };
}

#endif