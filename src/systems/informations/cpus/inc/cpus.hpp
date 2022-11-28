#pragma once

#ifndef SYSTEMS_INFORMATIONS_CPUS_HEADER
#define SYSTEMS_INFORMATIONS_CPUS_HEADER

#include "../../common.hpp"

namespace Systems::Informations::CPUs
{
    class CPU_Information :
        virtual public Systems::Informations::Information_Abstract
    {
        private:
            string m_manufacturer = "";

            string m_architecture = "";

            string m_model_name = "";

            string m_op_mode = "";

            int m_threads_per_socket = 0;

            int m_threads_per_core = 0;

            int m_clock_scaling = 0;

            int m_clock_max = 0;

            int m_clock_min = 0;

            int m_sockets = 0;

            int m_cpus = 0;

            array<string, 11> m_filters = {
                "Vendor ID:",
                "Model name:",
                "Architecture:",
                "CPU op-mode(s):",
                "CPU(s):",
                "Thread(s) per core:",
                "Core(s) per socket:",
                "Socket(s):",
                "CPU(s) scaling MHz:",
                "CPU max MHz:",
                "CPU min MHz:"
            };

        public:
            CPU_Information(
            ) : Systems::Informations::Information_Abstract()
            {
                string cpus, threads_per_core, threads_per_socket, 
                       sockets, clock_scaling, clock_max, clock_min;

                m_manufacturer = construct_information(
                    m_filters[0]
                );
                m_model_name = construct_information(
                    m_filters[1]
                );
                m_architecture = construct_information(
                    m_filters[2]
                );
                m_op_mode = construct_information(
                    m_filters[3]
                );
                cpus = construct_information(
                    m_filters[4]
                );
                threads_per_core = construct_information(
                    m_filters[5]
                );
                threads_per_socket = construct_information(
                    m_filters[6]
                );
                sockets = construct_information(
                    m_filters[7]
                );
                clock_scaling = construct_information(
                    m_filters[8]
                );
                clock_max = construct_information(
                    m_filters[9]
                );
                clock_min = construct_information(
                    m_filters[10]
                );

                m_threads_per_socket = atoi(threads_per_socket.c_str());
                m_threads_per_core = atoi(threads_per_core.c_str());
                m_clock_scaling = atoi(clock_scaling.c_str());
                m_clock_max = atoi(clock_max.c_str());
                m_clock_min = atoi(clock_min.c_str());
                m_sockets = atoi(sockets.c_str());
                m_cpus = atoi(cpus.c_str());
            }

            ~CPU_Information() = default;

            string get_manufacturer() { return m_manufacturer; }

            string get_architecture() { return m_architecture; }

            string get_model_name() { return m_model_name; }

            string get_op_mode() { return m_op_mode; }

            int get_threads_per_socket() { return m_threads_per_socket; }

            int get_threads_per_core() { return m_threads_per_core; }

            int get_clock_scaling() { return m_clock_scaling; }

            int get_clock_max() { return m_clock_max; }

            int get_clock_min() { return m_clock_min; }

            int get_sockets() { return m_sockets; }

            int get_cpus() { return m_cpus; }
    };
}

#endif