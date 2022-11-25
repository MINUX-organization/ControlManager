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
#include "../../../kernel/sockets/clients/inc/clients.hpp"
#include "../../../systems/informations/cpus/inc/cpus.hpp"
#include "../../../systems/informations/gpus/inc/gpus.hpp"
#include "../../../systems/informations/motherboards/inc/motherboards.hpp"

/**
 * @brief Contains classes to communicate with WEB-interface
 */
namespace Communicators::WEB_Interfaces
{
    /**
     * @brief Communicator with WEB-interface
     */
    class WEB_Interface_Communicator : 
        virtual public Kernel::Sockets::Clients::Client
    {
        private:
            enum WEB_Interface_Commands
            {
                system_info
            };

            std::mutex m_mutex;

            map<int, string> m_web_commands = {
                {WEB_Interface_Commands::system_info, "system-info"}
            };

            json construct_system_info(json payload)
            {
                Systems::Informations::CPUs::CPU_Information cpu_info;
                Systems::Informations::GPUs::GPU_Information gpu_info;
                Systems::Informations::Motherboards::Motherboard_Information motherboard_info;

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
                        {"manufacturer", cpu_info.get_manufacturer()},
                        {"model-name", cpu_info.get_model_name()},
                        {"architecture", cpu_info.get_architecture()},
                        {"op-modes", cpu_info.get_op_mode()},
                        {"cores", {
                            {"cpus", cpu_info.get_cpus()},
                            {"threads-per-core", cpu_info.get_threads_per_core()},
                            {"threads-per-socket", cpu_info.get_threads_per_socket()},
                            {"sockets", cpu_info.get_sockets()}
                        }}
                    }},
                    {"state", {
                        {"clocks-mhz", {
                            {"scalling", cpu_info.get_clock_scaling()},
                            {"max", cpu_info.get_clock_max()},
                            {"min", cpu_info.get_clock_min()}
                        }}
                    }}
                } : reply_payload["cpu"] = {};

                motherboard ? reply_payload["motherboard"] = {
                    {"information", {
                        {"manufacturer", motherboard_info.get_manufacturer()},
                        {"product-name", motherboard_info.get_product_name()},
                        {"serial-number", motherboard_info.get_serial_number()}
                    }}
                } : reply_payload["motherboard"] = {};

                // TODO: GPUs

                return reply_payload;
            }

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

            void start_command_handler()
            {
                string message;

                while (true)
                {
                    message = receive();
                    m_mutex.lock();
                    cout << message;
                    m_mutex.unlock();
                    std::this_thread::sleep_for(
                        std::chrono::milliseconds(500)
                    );
                }
            }

            void start_sending()
            {
                string message = "Hello from client\n";

                while (true)
                {
                    send(
                        message
                    );
                    std::this_thread::sleep_for(
                        std::chrono::milliseconds(1000)
                    );
                }
            }

        public:
            WEB_Interface_Communicator(
                string &host,
                size_t port
            ) : Kernel::Sockets::Clients::Client(
                    host,
                    port
                )
            {
            }

            virtual ~WEB_Interface_Communicator() = default;

            void start()
            {
                std::vector<std::thread> threads;

                create_connection();

                // auto sender = std::async(
                //     std::launch::async,
                //     &Communicators::WEB_Interfaces::WEB_Interface_Communicator::start_sending,
                //     this
                // );

                // auto receiver = std::async(
                //     std::launch::async,
                //     &Communicators::WEB_Interfaces::WEB_Interface_Communicator::start_command_handler,
                //     this
                // );

                threads.push_back(
                    std::thread(
                        &Communicators::WEB_Interfaces::WEB_Interface_Communicator::start_command_handler,
                        this
                    )
                );
                threads.push_back(
                    std::thread(
                        &Communicators::WEB_Interfaces::WEB_Interface_Communicator::start_sending,
                        this
                    )
                );

                for (auto &t : threads)
                    t.join();



                // fd_set read_fds;
                // fd_set write_fds;
                // fd_set except_fds;

                // int maxfd = m_socket;

                // while (1)
                // {
                //     FD_ZERO(&read_fds);
                //     FD_SET(STDIN_FILENO, &read_fds);
                //     FD_SET(m_socket, &read_fds);
                    
                //     FD_ZERO(&write_fds);
                //     FD_SET(m_socket, &write_fds);
                    
                //     FD_ZERO(&except_fds);
                //     FD_SET(STDIN_FILENO, &except_fds);
                //     FD_SET(m_socket, &except_fds);

                //     int activity = select(
                //         maxfd + 1,
                //         &read_fds,
                //         &write_fds,
                //         &except_fds,
                //         NULL
                //     );

                //     switch (activity)
                //     {
                //         default:
                //             if (FD_ISSET(m_socket, &write_fds))
                //             {

                //             }
                //             if (FD_ISSET(m_socket, &read_fds))
                //             {
                //                 string message = receive();
                //                 cout << message << endl;
                //                 std::this_thread::sleep_for(
                //                     std::chrono::milliseconds(1000)
                //                 );
                //             }
                //     }
                // }
            }
    };
}

#endif