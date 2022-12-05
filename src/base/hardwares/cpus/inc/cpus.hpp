#pragma once

#ifndef BASE_CPUS_HEADER
#define BASE_CPUS_HEADER

#include "../../common.hpp"

#include "../../../../systems/informations/cpus/inc/cpus.hpp"
#include "../../../../systems/masters/cpus/inc/cpus.hpp"

namespace Base::Hardwares::CPUs
{
    class CPU : 
        virtual public Base::Hardwares::Abstracts::Hardware_Abstract
    {
        private:
            Systems::Masters::CPUs::CPU m_master;

            Systems::Informations::CPUs::CPU m_information;

        public:
            CPU() : Base::Hardwares::Abstracts::Hardware_Abstract()
            {
            }

            ~CPU() = default;

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
                        {"model-name", m_information.get_model_name()},
                        {"architecture", m_information.get_architecture()},
                        {"op-modes", m_information.get_op_mode()},
                        {"cores", {
                            {"cpus", m_information.get_cpus()},
                            {"threads-per-core", m_information.get_threads_per_core()},
                            {"threads-per-socket", m_information.get_threads_per_socket()},
                            {"sockets", m_information.get_sockets()}
                        }}
                    }},
                    {"state", {
                        {"clocks-mhz", {
                            {"scalling", m_information.get_clock_scaling()},
                            {"max", m_information.get_clock_max()},
                            {"min", m_information.get_clock_min()}
                        }}
                    }}
                };

                return result;
            }
    };
}

#endif