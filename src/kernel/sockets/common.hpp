/**
 * @file common.hpp
 * @author Daniil Ibragimov (ghaghal93@gmail.com)
 * @brief Common file for sockets files
 * @version 0.1
 * @date 2022-11-10
 * 
 * @copyright Copyright (c) 2022
 */

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

/**
 * @brief Abstract for sockets
 */
namespace Kernel::Sockets::Abstracts
{
    /**
     * @brief Socket abstract class
     */
    class Socket_Abstract
    {
        private:

        protected:
            /**
             * @brief Host
             */
            string m_host;

            /**
             * @brief Port
             */
            in_port_t m_port;

            /**
             * @brief Address
             */
            struct sockaddr_in m_address;

            /**
             * @brief Socket status
             */
            int m_socket;

            /**
             * @brief Client socket
             */
            int m_client_socket;

            /**
             * @brief Length of address
             */
            int m_addrlen = sizeof(m_address);

            /**
             * @brief SSL context
             */
            SSL_CTX* m_ctx;

            /**
             * @brief SSL socket
             */
            SSL* m_ssl;

        public:
            /**
             * @brief Construct a new Socket_Abstract object
             * 
             * @param host Host 
             * @param port Port
             */
            Socket_Abstract(
                const string &host,
                int port
            ) : m_host(host),
                m_port(port)
            {
            }

            /**
             * @brief Destroy the Socket_Abstract object
             */
            virtual ~Socket_Abstract() = default;
    };
}

#endif