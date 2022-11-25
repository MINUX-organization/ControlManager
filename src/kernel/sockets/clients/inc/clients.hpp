#pragma once

#ifndef KERNEL_SOCKETS_CLIENTS_HEADER
#define KERNEL_SOCKETS_CLIENTS_HEADER

#include "../../common.hpp"

#include <netinet/tcp.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>
#include <netdb.h>
#include <fcntl.h>

namespace Kernel::Sockets::Clients
{
    class Client
    {
        private:

        protected:
            string m_host{ 0 };

            size_t m_port{ 0 };

            int m_socket;

            void create_connection()
            {
                // struct sockaddr_in serv_addr;

                // m_socket = socket(
                //     AF_INET,
                //     SOCK_STREAM,
                //     0
                // );

                // serv_addr.sin_family = AF_INET;
                // serv_addr.sin_port = htons(m_port);

                // inet_pton(
                //     AF_INET,
                //     m_host.c_str(),
                //     &serv_addr.sin_addr
                // );

                // connect(
                //     m_socket,
                //     (struct sockaddr*)&serv_addr,
                //     sizeof(serv_addr)
                // );

                struct hostent* hp;

                int on = 1;

                struct sockaddr_in addr;

                hp = gethostbyname(
                    m_host.c_str()
                );

                if (hp == NULL)
                    // TODO: Error: Couldnot determine host
                    exit(1);
                
                bcopy(
                    hp->h_addr_list[0],
                    &addr.sin_addr,
                    hp->h_length
                );

                addr.sin_port = htons(
                    m_port
                );
                addr.sin_family = AF_INET;

                m_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

                setsockopt(
                    m_socket,
                    IPPROTO_TCP,
                    TCP_NODELAY,
                    (const char*)&on,
                    sizeof(int)
                );

                if (m_socket == -1)
                    // TODO: Error: Couldnot create socket
                    exit(1);

                int res = connect(
                    m_socket, 
                    (struct sockaddr*)&addr,
                    sizeof(struct sockaddr_in)
                );

                if(res != 0)
                    // TODO: Error: Couldnot create connection
                    exit(1);
            }

            void send(
                string message
            )
            {
                int iTotal = 0, iSent = 0, iBytes = 0;

                const char* pMessage = message.c_str();

                size_t ulMessage_size = message.size();

                iTotal = ulMessage_size;

                do {
                    iBytes = write(
                        m_socket,
                        pMessage + iSent,
                        iTotal - iSent
                    );

                    if (iBytes < 0)
                        // TODO: Error: While writing
                        break;
                    
                    if (iBytes == 0)
                        break;
                    
                    iSent += iBytes;
                } while (iSent < iTotal);
            }

            string receive()
            {
                int size = 4098;
                int total = size - 1, received = 0, bytes = 0;

                char buffer[4098];

                bzero(
                    buffer,
                    size
                );

                do {
                    // bytes = read(
                    bytes = recv(
                        m_socket,
                        buffer + received,
                        total - received,
                        MSG_DONTWAIT
                    );

                    if (bytes < 0)
                        // TODO: Error: While receiving
                        break;
                    
                    if (bytes == 0)
                        break;
                    
                    received += bytes;
                } while(received < total);

                return string(buffer);
            }

            void async_send()
            {

            }

        public:
            Client(
                string &host,
                size_t port
            ) : m_host(host),
                m_port(port)
            {

            }

            virtual ~Client()
            {
                shutdown(
                    m_socket,
                    SHUT_RDWR
                );
                close(
                    m_socket
                );
            }
    };
}

#endif