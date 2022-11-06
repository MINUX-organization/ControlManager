#pragma once

#ifndef KERNEL_SOCKETS_SERVERS_HEADER
#define KERNEL_SOCKETS_SERVERS_HEADER

#include "../../common.hpp"

namespace Kernel::Sockets::Servers
{
    class Server :
        virtual public Kernel::Sockets::Abstracts::Socket_Abstract
    {
        private:

        public:
            Server(
                string &host,
                int port
            ) : Kernel::Sockets::Abstracts::Socket_Abstract(
                    host,
                    port
                )
            {
                int error;
                int opt = 1;

                m_socket = socket(
                    AF_INET, 
                    SOCK_STREAM, 
                    0
                );
            
                if (m_socket < 0)
                    // TODO: Handle error
                    exit(EXIT_FAILURE);
            
                error = setsockopt(
                    m_socket, 
                    SOL_SOCKET,
                    SO_REUSEADDR | SO_REUSEPORT, 
                    &opt,
                    sizeof(opt)
                );

                if (error != 0) 
                    // TODO: Handle error
                    exit(EXIT_FAILURE);

                m_address.sin_family = AF_INET;
                m_address.sin_addr.s_addr = INADDR_ANY;
                m_address.sin_port = htons(port);

                error = bind(
                    m_socket, 
                    (struct sockaddr*)&m_address,
                    sizeof(m_address)
                );

                if (error < 0)
                    // TODO: Handle error
                    exit(EXIT_FAILURE);

                error = listen(
                    m_socket, 
                    3
                );

                if (error < 0)
                    // TODO: Handle error
                    exit(EXIT_FAILURE);

            }

            virtual ~Server()
            {
                close(m_client_socket);
                shutdown(m_socket, SHUT_RDWR);
            }

            string get()
            {
                char buffer[1024];

                read(
                    m_client_socket,
                    buffer,
                    1024
                );

                string output(buffer);

                return output;
            }

            void write(string &message)
            {
                send(
                    m_client_socket,
                    message.c_str(),
                    strlen(message.c_str()),
                    0
                );
            }

            void start()
            {
                m_client_socket = accept(
                    m_socket,
                    (struct sockaddr*)&m_address,
                    (socklen_t*)&m_addrlen
                );
            }
    };
}

#endif