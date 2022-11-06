#pragma once

#ifndef KERNEL_SOCKETS_COMMON_HEADER
#define KERNEL_SOCKETS_COMMON_HEADER

#include "../common.hpp"

#include <openssl/ssl.h>
#include <netinet/tcp.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <semaphore.h>
#include <unistd.h>
#include <fcntl.h>
#include <netdb.h>

namespace Kernel::Sockets::Abstracts
{
    class Socket_Abstract
    {
        private:

        protected:
            string m_host;

            in_port_t m_port;

            struct sockaddr_in m_address;

            int m_socket;

            int m_client_socket;

            int m_addrlen = sizeof(m_address);

            SSL_CTX* m_ctx;

            SSL* m_ssl;

        public:
            Socket_Abstract(
                const string &host,
                int port
            ) : m_host(host),
                m_port(port)
            {
            }

            virtual ~Socket_Abstract() = default;
    };
}

#endif