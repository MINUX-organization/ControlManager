#pragma once

#ifndef KERNEL_SOCKETS_CLIENTS_HEADER
#define KERNEL_SOCKETS_CLIENTS_HEADER

#include "../../common.hpp"

namespace Kernel::Sockets::Clients
{
    class Client : 
        virtual public Kernel::Sockets::Abstracts::Socket_Abstract
    {
        private:

        public:
            Client(
                string &host,
                int port
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

            virtual ~Client()
            {
                shutdown(m_socket, SHUT_RDWR);
            }

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

            void write(
                string &message
            )
            {
                send(
                    m_socket, 
                    message.c_str(),
                    strlen(message.c_str()), 
                    0
                );
            }

            string get()
            {
                char buffer[1024];

                read(
                    m_socket,
                    buffer,
                    1024
                );

                string output(buffer);

                return output;
            }
    };
}


#endif