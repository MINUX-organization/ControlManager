/**
 * @file web_interfaces.hpp
 * @author Daniil Ibragimov (ghaghal93@gmail.com)
 * @brief Contains classes to communicate with WEB-interface
 * @version 0.1
 * @date 2022-11-10
 * 
 * @copyright Copyright (c) 2022
 */

#pragma once

#ifndef COMMUNICATORS_WEB_INTERFACES_HEADER
#define COMMUNICATORS_WEB_INTERFACES_HEADER

#include "../../common.hpp"

#include "../../../systems/informations/motherboards/inc/motherboards.hpp"
#include "../../../systems/informations/cpus/inc/cpus.hpp"
#include "../../../systems/informations/gpus/inc/gpus.hpp"

/**
 * @brief Contains classes to communicate with WEB-interface
 */
namespace Communicators::WEB_Interfaces
{
    /**
     * @brief Commands list from WEB-interface
     */
    enum WEB_Interface_Commands
    {
        system_info
    };

    /**
     * @brief Communicator with WEB-interface
     */
    class WEB_Interface_Communicator
    {
        private:
            /**
             * @brief Socket client
             */
            Kernel::Sockets::Clients::Client m_client;

            /**
             * @brief CPU Info object
             */
            Systems::Informations::CPUs::CPU_Information m_cpu_info;

            /**
             * @brief GPU Info object
             */
            Systems::Informations::GPUs::GPU_Information m_gpu_info;

            /**
             * @brief Motherboard object
             */
            Systems::Informations::Motherboards::Motherboard_Information m_motherboard_info;

            /**
             * @brief Map of web-interface commands
             */
            map<int, string> m_web_commands = {
                {0, "system-info"}
            };

            /**
             * @brief Construct new message to send to web-interface
             * 
             * @param message Message
             * @param command ID of command
             * @return json 
             */
            json construct_message(json &message, int command)
            {
                json reply = {};
                json reply_payload = {};
                json payload = {};

                string id;

                vector<int> gpu;

                bool cpu;
                bool motherboard;

                if (!message.contains("id"))
                    // TODO: Handle error
                    exit(EXIT_FAILURE);
                
                if (!message.contains("payload"))
                    // TODO: Handle error
                    exit(EXIT_FAILURE);

                id = message["id"];

                payload = message["payload"];

                if (command == Communicators::WEB_Interfaces::system_info)
                {
                    if (payload.contains("cpu"))
                        cpu = payload["cpu"];
                    if (payload.contains("motherboard"))
                        motherboard = payload["motherboard"];
                    if (payload.contains("gpu"))
                        for (auto &elem : payload["gpu"])
                            gpu.push_back(elem);

                    reply["response-id"] = id;
                    // TODO: Generate random string
                    reply["id"] = "aaaaa";

                    cpu ? reply_payload["cpu"] = {
                        {"information", {
                            {"manufacturer", m_cpu_info.get_manufacturer()},
                            {"model-name", m_cpu_info.get_model_name()},
                            {"architecture", m_cpu_info.get_architecture()},
                            {"op-modes", m_cpu_info.get_op_mode()},
                            {"cores", {
                                {"cpus", m_cpu_info.get_cpus()},
                                {"threads-per-core", m_cpu_info.get_threads_per_core()},
                                {"threads-per-socket", m_cpu_info.get_threads_per_socket()},
                                {"sockets", m_cpu_info.get_sockets()}
                            }}
                        }},
                        {"state", {
                            {"clocks-mhz", {
                                {"scalling", m_cpu_info.get_clock_scaling()},
                                {"max", m_cpu_info.get_clock_max()},
                                {"min", m_cpu_info.get_clock_min()}
                            }}
                        }}
                    } : reply_payload["cpu"] = {};

                    motherboard ? reply_payload["motherboard"] = {
                        {"information", {
                            {"manufacturer", m_motherboard_info.get_manufacturer()},
                            {"product-name", m_motherboard_info.get_product_name()},
                            {"serial-number", m_motherboard_info.get_serial_number()}
                        }}
                    } : reply_payload["motherboard"] = {};

                    reply["payload"] = reply_payload;
                }

                return reply;
            }

            /**
             * @brief Parse message from web-interface
             * 
             * @param message Message
             * @return json 
             */
            json parse_message(json &message)
            {
                json reply = {};

                if (message.contains("command"))
                {
                    string command = message["command"];

                    for (size_t i = 0; i < m_web_commands.size(); i++)
                        if (command == m_web_commands[i])
                            reply = construct_message(message, i);
                } else {
                    // TODO: Handle error
                }

                return reply;
            }

        public:
            /**
             * @brief Construct a new web interface communicator object
             * 
             * @param configuration Configuration
             */
            WEB_Interface_Communicator(
                json &configuration
            ) : m_client(
                    static_cast<string>(configuration["host"]),
                    static_cast<int>(configuration["port"])
                )
            {
            }

            /**
             * @brief Destroy the web interface communicator object
             */
            virtual ~WEB_Interface_Communicator() = default;

            /**
             * @brief Create a connection
             */
            void create_connection()
            {
                m_client.create_connection();
            }

            /**
             * @brief Send statistic
             */
            void send_statistic()
            {

            }

            /**
             * @brief Handle request from WEB-interface
             */
            void handle_request()
            {
                string read_str;
                string reply_str;

                json read;
                json reply;

                while (true)
                {
                    read_str = m_client.read_message();

                    if (read_str.size() > 0)
                    {
                        read = json::parse(read_str);

                        reply = parse_message(read);

                        reply_str = reply.dump();

                        cout << reply_str << endl;
                        // m_client.send_message(reply_str);
                    }

                    sleep_for(milliseconds(1000));
                }
            }
    };
}

#endif