/**
 * @file web_interfaces.hpp
 * @author your name (you@domain.com)
 * @brief Contains managers for web interface
 * @version 0.1
 * @date 2022-11-17
 * 
 * @copyright Copyright (c) 2022
 */

#pragma once

#ifndef MANAGERS_WEB_INTERFACES_HEADER
#define MANAGERS_WEB_INTERFACES_HEADER

#include "../../common.hpp"

#include "../../../systems/informations/motherboards/inc/motherboards.hpp"
#include "../../../systems/informations/cpus/inc/cpus.hpp"
#include "../../../systems/informations/gpus/inc/gpus.hpp"

/**
 * @brief Contains managers for web interface
 */
namespace Managers::WEB_Interfaces
{
    /**
     * @brief Manager for WEB-Interface
     */
    class WEB_Interface_Manager
    {
        private:
            /**
             * @brief Commands ID
             */
            enum WEB_Interface_Commands
            {
                system_info
            };

            /**
             * @brief CPU Info
             */
            Systems::Informations::CPUs::CPU_Information m_cpu_info;

            /**
             * @brief GPU Info
             */
            Systems::Informations::GPUs::GPU_Information m_gpu_info;

            /**
             * @brief Motherboard info
             */
            Systems::Informations::Motherboards::Motherboard_Information m_motherboard_info;

            /**
             * @brief Map of commands
             */
            map<int, string> m_web_commands = {
                {WEB_Interface_Commands::system_info, "system-info"}
            };

            /**
             * @brief Construct payload for system info command
             * 
             * @param payload Payload of message
             * @return json 
             */
            json construct_system_info(json payload)
            {
                json reply_payload;

                string id;

                vector<int> gpus;

                bool cpu, motherboard;

                if (payload.contains("cpu"))
                    cpu = payload["cpu"];
                    // TODO: Error: Cannot convert cpu to bool
                if (payload.contains("motherboard"))
                    motherboard = payload["motherboard"];
                    // TODO: Error: Cannot convert motherboard to bool
                if (payload.contains("gpu"))
                    for (auto &elem : payload["gpu"])
                        gpus.push_back(elem);
                        // TODO: Error: Cannot convert gpu to array of int

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

                // TODO: GPUs

                return reply_payload;
            }

            /**
             * @brief Construct reply for server
             * 
             * @param id ID of request
             * @param payload Payload of message
             * @param command_id Command ID
             * @return json 
             */
            json construct_reply(string &id, json &payload, size_t command_id)
            {
                json reply, reply_payload;

                switch(command_id)
                {
                    case WEB_Interface_Commands::system_info:
                    {
                        reply_payload = construct_system_info(payload);
                        break;
                    }
                    default:
                    {
                        // TODO: Error: No command ID found
                        break;
                    }
                }

                reply["response-id"] = id;
                reply["id"] = "aaaaaa";
                // TODO: Generate random string
                reply["payload"] = reply_payload;

                return reply;
            }

        public:
            /**
             * @brief Construct a new web interface manager object
             */
            WEB_Interface_Manager() = default;

            /**
             * @brief Destroy the web interface manager object
             */
            virtual ~WEB_Interface_Manager() = default;

            /**
             * @brief Parse message
             * 
             * @param message Message
             * @return json Response
             */
            json parse_message(
                string &message
            )
            {
                json message_json, reply, payload;
                string command, id;

                message_json = json::parse(message);
                // TODO: Error: if can't be parsed

                if (!message_json.contains("id"))
                    // TODO: Error: No ID of message found
                    exit(EXIT_FAILURE);
                
                if (!message_json.contains("payload"))
                    // TODO: Error: No payload found
                    exit(EXIT_FAILURE);

                if (!message_json.contains("command"))
                    // TODO: Error: No command found
                    exit(EXIT_FAILURE);

                id = message_json["id"];
                // TODO: Error: Cannot convert id to string
                command = message_json["command"];
                // TODO: Error: Cannot convert command to string
                payload = message_json["payload"];
                // TODO: Error: Cannot convert payload to json

                for (size_t i = 0; i < m_web_commands.size(); i++)
                    if (command == m_web_commands[i]) {
                        reply = construct_reply(id, payload, i);
                    } else {
                        // TODO: Error: There is no command ID
                        exit(EXIT_FAILURE);
                    }

                return reply;
            }
    };
}

#endif