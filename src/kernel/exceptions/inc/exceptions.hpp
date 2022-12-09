#pragma once

#ifndef KERNEL_EXCEPTIONS_HEADER
#define KERNEL_EXCEPTIONS_HEADER

#include "../common.hpp"

#include <nvml.h>
#include <NVCtrl/NVCtrl.h>
#include <NVCtrl/NVCtrlLib.h>

#include <fcntl.h>
#include <xf86drm.h>
#include <sys/ioctl.h>
#include <xf86drmMode.h>
#include <libdrm/amdgpu.h>
#include <libdrm/amdgpu_drm.h>

namespace Kernel::Exceptions::Managers::Factories
{
    class Error_Open_Display :
        virtual public Kernel::Exceptions::Abstracts::Exception_Abstract
    {
        private:
            Display* m_pDisplay;

        public:
            Error_Open_Display(
                Display *pDisplay
            ) : Kernel::Exceptions::Abstracts::Exception_Abstract(),
                m_pDisplay(pDisplay)
            {
                m_message = "Could not open X display. Check if $DISPLAY is set";
            }

            virtual ~Error_Open_Display() = default;
    };

    class Error_Query_Nvidia_Amount :
        virtual public Kernel::Exceptions::Abstracts::Exception_Abstract
    {
        private:
            Display *m_pDisplay;

        public:
            Error_Query_Nvidia_Amount(
                Display *pDisplay
            ) : m_pDisplay(pDisplay)
            {
                m_message = "Could not query amount of Nvidia GPUs";
            }

            virtual ~Error_Query_Nvidia_Amount() = default;
    };
}

namespace Kernel::Exceptions::Sockets::Clients
{
    class Error_Bad_Host :
        virtual public Kernel::Exceptions::Abstracts::Exception_Abstract
    {
        private:
            string m_host;

        public:
            Error_Bad_Host(
                const char* host
            ) : Kernel::Exceptions::Abstracts::Exception_Abstract(),
                m_host(host)
            {
                m_message = "Could not determine host: " + m_host;
            }
        
            virtual ~Error_Bad_Host() = default;
    };

    class Error_Socket_Creation :
        virtual public Kernel::Exceptions::Abstracts::Exception_Abstract
    {
        private:
            int m_socket;

        public:
            Error_Socket_Creation(
                int socket
            ) : Kernel::Exceptions::Abstracts::Exception_Abstract(),
                m_socket(socket)
            {
                m_message = "Could not create socket: " + std::to_string(m_socket);
            }

            virtual ~Error_Socket_Creation() = default;
    };

    class Error_Bad_Connection :
        virtual public Kernel::Exceptions::Abstracts::Exception_Abstract
    {
        private:
            int m_connection;

        public:
            Error_Bad_Connection(
                int connection
            ) : Kernel::Exceptions::Abstracts::Exception_Abstract(),
                m_connection(connection)
            {
                m_message = "Could not create connection: " + std::to_string(m_connection);
            }

            virtual ~Error_Bad_Connection() = default;
    };

    class Error_Sending_Message :
        virtual public Kernel::Exceptions::Abstracts::Exception_Abstract
    {
        private:
            int m_socket;

            string m_sent_message;

            int m_sent;

            int m_total;

        public:
            Error_Sending_Message(
                int socket,
                const char *pMessage,
                int sent,
                int total
            ) : Kernel::Exceptions::Abstracts::Exception_Abstract(),
                m_socket(socket),
                m_sent_message(pMessage),
                m_sent(sent),
                m_total(total)
            {
                m_message = "Could not write a message. Socket: " +
                    std::to_string(m_socket) +
                    ", Sent: " + std::to_string(m_sent) +
                    ", Total: " + std::to_string(m_total);
            }

            virtual ~Error_Sending_Message() = default;
    };

    class Error_Receiving_Message :
        virtual public Kernel::Exceptions::Abstracts::Exception_Abstract
    {
        private:
            int m_socket;

            string m_buffer;

            int m_received;

            int m_total;

        public:
            Error_Receiving_Message(
                int socket,
                char buffer[4096],
                int received,
                int total
            ) : Kernel::Exceptions::Abstracts::Exception_Abstract(),
                m_socket(socket),
                m_buffer(buffer),
                m_received(received),
                m_total(total)
            {
                m_message = "Could not receive a message: Socket: " +
                    std::to_string(m_socket) +
                    ", Received: " + std::to_string(m_received) +
                    ", Total: " + std::to_string(m_total);
            }

            virtual ~Error_Receiving_Message() = default;
    };
}

namespace Kernel::Exceptions::Systems::Masters::GPUs::Nvidias
{
    class Error_Query_String_Attribute :
        virtual public Kernel::Exceptions::Abstracts::Exception_Abstract
    {
        private:
            int m_target_type;

            size_t m_gpu_id;

            unsigned int m_attribute;

        public:
            Error_Query_String_Attribute(
                int target_type,
                size_t gpu_id,
                unsigned int attribute
            ) : Kernel::Exceptions::Abstracts::Exception_Abstract(),
                m_target_type(target_type),
                m_gpu_id(gpu_id),
                m_attribute(attribute)
            {
                m_message = "Could not query string attribute. Target type: " +
                    std::to_string(target_type) +
                    ", GPU ID: " + std::to_string(gpu_id) +
                    ", Attribute: " + std::to_string(attribute);
            }

            virtual ~Error_Query_String_Attribute() = default;
    };

    class Error_Query_Int_Attribute :
        virtual public Kernel::Exceptions::Abstracts::Exception_Abstract
    {
        private:
            int m_target_type;

            size_t m_gpu_id;

            unsigned int m_attribute;

        public:
            Error_Query_Int_Attribute(
                int target_type,
                size_t gpu_id,
                unsigned int attribute
            ) : Kernel::Exceptions::Abstracts::Exception_Abstract(),
                m_target_type(target_type),
                m_gpu_id(gpu_id),
                m_attribute(attribute)
            {
                m_message = "Could not query int attribute. Target type: " +
                    std::to_string(target_type) +
                    ", GPU ID: " + std::to_string(gpu_id) +
                    ", Attribute: " + std::to_string(attribute);
            }

            virtual ~Error_Query_Int_Attribute() = default;
    };

    class Error_Query_Value_Attribute :
        virtual public Kernel::Exceptions::Abstracts::Exception_Abstract
    {
        private:
            int m_target_type;

            size_t m_gpu_id;

            unsigned int m_attribute;

        public:
            Error_Query_Value_Attribute(
                int target_type,
                size_t gpu_id,
                unsigned int attribute
            ) : Kernel::Exceptions::Abstracts::Exception_Abstract(),
                m_target_type(target_type),
                m_gpu_id(gpu_id),
                m_attribute(attribute)
            {
                m_message = "Could not query value attribute. Target type: " +
                    std::to_string(target_type) +
                    ", GPU ID: " + std::to_string(gpu_id) +
                    ", Attribute: " + std::to_string(attribute);
            }

            virtual ~Error_Query_Value_Attribute() = default;
    };

    class Error_Set_Int_Attribute :
        virtual public Kernel::Exceptions::Abstracts::Exception_Abstract
    {
        private:
            int m_target_type;

            size_t m_gpu_id;

            unsigned int m_attribute;

        public:
            Error_Set_Int_Attribute(
                int target_type,
                size_t gpu_id,
                unsigned int attribute
            ) : Kernel::Exceptions::Abstracts::Exception_Abstract(),
                m_target_type(target_type),
                m_gpu_id(gpu_id),
                m_attribute(attribute)
            {
                m_message = "Could not set int attribute. Target type: " +
                    std::to_string(target_type) +
                    ", GPU ID: " + std::to_string(gpu_id) +
                    ", Attribute: " + std::to_string(attribute);
            }

            virtual ~Error_Set_Int_Attribute() = default;
    };

    class Error_XNVCtrl_Not_Found :
        virtual public Kernel::Exceptions::Abstracts::Exception_Abstract
    {
        private:
            Display *m_pDisplay;

        public:
            Error_XNVCtrl_Not_Found(
                Display *pDisplay
            ) : Kernel::Exceptions::Abstracts::Exception_Abstract(),
                m_pDisplay(pDisplay)
            {
                m_message = "XNVCtrl extension doesn't exist on m_pDisplay";
            }
        
            virtual ~Error_XNVCtrl_Not_Found() = default;

            Display* get_display() { return m_pDisplay; }
    };

    class Error_Set_Power_Limit :
        virtual public Kernel::Exceptions::Abstracts::Exception_Abstract
    {
        private:
            nvmlDevice_t *m_device;

            size_t m_power_limit;
        
        public:
            Error_Set_Power_Limit(
                nvmlDevice_t *device,
                size_t power_limit
            ) : Kernel::Exceptions::Abstracts::Exception_Abstract(),
                m_device(device),
                m_power_limit(power_limit)
            {
                m_message = "Could not set power limit to device: " + std::to_string(m_power_limit);
            }

            virtual ~Error_Set_Power_Limit() = default;
    };
}

#endif