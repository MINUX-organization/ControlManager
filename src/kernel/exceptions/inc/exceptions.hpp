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
}

#endif