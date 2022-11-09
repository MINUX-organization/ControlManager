/**
 * @file clients.hpp
 * @author Daniil Ibragimov (ghaghal93@gmail.com)
 * @brief Contains clients for sockets
 * @version 0.1
 * @date 2022-11-10
 * 
 * @copyright Copyright (c) 2022
 */

#pragma once

#ifndef KERNEL_SOCKETS_CLIENTS_HEADER
#define KERNEL_SOCKETS_CLIENTS_HEADER

#include "../../common.hpp"

/**
 * @brief Contains clients for sockets
 */
namespace Kernel::Sockets::Clients
{
    /**
     * @brief Client to connect server
     */
    class Client : 
        virtual public Kernel::Sockets::Abstracts::Socket_Abstract
    {
        private:

        public:
            /**
             * @brief Construct a new Client object
             * 
             * @param host Host
             * @param port Port
             */
            Client(
                const string &host,
                const int port
            ) : Kernel::Sockets::Abstracts::Socket_Abstract(
                    host,
                    port
                )
            {
                int error;

                m_socket = socket(
                    AF_INET, 
                    SOCK_STREAM, 
                    0
                );

                if (m_socket < 0)
                    // TODO: Handle error
                    exit(EXIT_FAILURE);
            
                m_address.sin_family = AF_INET;
                m_address.sin_port = htons(port);

                error = inet_pton(
                    AF_INET, 
                    host.c_str(), 
                    &m_address.sin_addr
                );

                if (error <= 0)
                    // TODO: Handle error
                    exit(EXIT_FAILURE);
            }

            /**
             * @brief Destroy the Client object
             */
            virtual ~Client()
            {
                shutdown(m_socket, SHUT_RDWR);
            }

            /**
             * @brief Create a connection
             * 
             */
            void create_connection()
            {
                int error = connect(
                    m_socket,
                    (struct sockaddr*)&m_address,
                    sizeof(m_address)
                );

                if (m_socket < 0)
                    // TODO: Handle error
                    exit(EXIT_FAILURE);
            }

            /**
             * @brief Send message to server
             * 
             * @param message Message
             */
            void send_message(
                string &message
            )
            {
                int total = 1024, sent = 0, bytes = 0;

                char *buffer = new char[message.length() + 1];

                strcpy(buffer, message.c_str());

                do {
                    bytes = write(
                        m_socket,
                        buffer + sent,
                        total - sent
                    );
                    if (bytes < 0)
                        // TODO: Handle error
                        break;
                    if (bytes == 0)
                        break;
                    sent += bytes;
                } while (sent < total);
            }

            /**
             * @brief Read message from server
             * 
             * @return string 
             */
            string read_message()
            {
                char buffer[1024];
                int total = 1024, received = 0, bytes = 0;

                bzero(
                    buffer,
                    total
                );

                do {
                    bytes = read(
                        m_socket,
                        buffer + received,
                        total - received
                    );
                    if (bytes < 0)
                        // TODO: Handle error
                        break;
                    if (bytes == 0)
                        break;
                    received += bytes;
                } while(received < total);

                string output(buffer);

                return output;
            }
    };
}


#endif