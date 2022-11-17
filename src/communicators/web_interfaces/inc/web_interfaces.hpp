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
#include "../../../managers/web_interfaces/inc/web_interfaces.hpp"

/**
 * @brief Contains classes to communicate with WEB-interface
 */
namespace Communicators::WEB_Interfaces
{
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
                        cout << reply_str << endl;
                    }

                    sleep_for(milliseconds(1000));
                }
            }
    };
}

#endif