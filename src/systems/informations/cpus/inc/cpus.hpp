#pragma once

#ifndef SYSTEMS_INFORMATIONS_CPUS_HEADER
#define SYSTEMS_INFORMATIONS_CPUS_HEADER

#include "../../common.hpp"

namespace Systems::Informations::CPUs
{
    class CPU :
        virtual public Systems::Informations::Abstracts::Information_Abstract
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

            vector<string> m_filters = {
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
            CPU(
            ) : Systems::Informations::Abstracts::Information_Abstract()
            {
            }

            ~CPU() = default;

            void construct(
                vector<string> &raw_informations
            )
            {
                for (size_t i = 0; i < raw_informations.size(); i++)
                    filter_output(
                        raw_informations[i],
                        m_filters[i]
                    );

                m_manufacturer = raw_informations[0];
                m_model_name = raw_informations[1];
                m_architecture = raw_informations[2];
                m_op_mode = raw_informations[3];
                m_cpus = atoi(raw_informations[4].c_str());
                m_threads_per_core = atoi(raw_informations[5].c_str());
                m_threads_per_socket = atoi(raw_informations[6].c_str());
                m_sockets = atoi(raw_informations[7].c_str());
                m_clock_scaling = atoi(raw_informations[8].c_str());
                m_clock_max = atoi(raw_informations[9].c_str());
                m_clock_min = atoi(raw_informations[10].c_str());
            }

            vector<string> get_filters() { return m_filters; }

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