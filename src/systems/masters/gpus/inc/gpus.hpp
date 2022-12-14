#pragma once

#ifndef SYSTEMS_MASTERS_GPUS_HEADER
#define SYSTEMS_MASTERS_GPUS_HEADER

#include "abstracts.hpp"

#include <nvml.h>
#include <NVCtrl/NVCtrl.h>
#include <NVCtrl/NVCtrlLib.h>

#include <fcntl.h>
#include <xf86drm.h>
#include <sys/ioctl.h>
#include <xf86drmMode.h>
#include <libdrm/amdgpu.h>
#include <libdrm/amdgpu_drm.h>

namespace Systems::Masters::GPUs
{
    /**
     * @brief Nvidia GPU Communicator
     */
    class Nvidia :
        virtual public Systems::Masters::GPUs::Abstracts::GPU_Master_Abstract
    {
        private:
            /**
             * @brief Device object
             */
            nvmlDevice_t *m_device = new nvmlDevice_t;

            /**
             * @brief Xorg display object
             */
            Display *m_pDisplay;

            /**
             * @brief Query attribute and get string response
             * 
             * @param target_type What to query
             * @param attribute What attribute
             * @return string 
             */
            string query_string_attribute(
                int target_type,
                unsigned int attribute
            )
            {
                char *str;

                bool error = XNVCTRLQueryTargetStringAttribute(
                    m_pDisplay,
                    target_type,
                    m_gpu_id,
                    0,
                    attribute,
                    &str
                );

                if (!error)
                    throw Kernel::Exceptions::Systems::Masters::GPUs::Nvidias::Error_Query_String_Attribute(
                        target_type,
                        m_gpu_id,
                        attribute
                    );
                
                return string(str);
            }

            /**
             * @brief Query attribute and get int response
             * 
             * @param target_type What to query
             * @param attribute What attribute
             * @return int 
             */
            int query_int_attribute(
                int target_type,
                unsigned int attribute
            )
            {
                int res;

                bool error = XNVCTRLQueryTargetAttribute(
                    m_pDisplay,
                    target_type,
                    m_gpu_id,
                    0,
                    attribute,
                    &res
                );

                if (!error)
                    throw Kernel::Exceptions::Systems::Masters::GPUs::Nvidias::Error_Query_Int_Attribute(
                        target_type,
                        m_gpu_id,
                        attribute
                    );

                return res;
            }

            /**
             * @brief Query attribute and get object response
             * 
             * @param target_type What to query
             * @param attribute What attribute
             * @return NVCTRLAttributeValidValuesRec 
             */
            NVCTRLAttributeValidValuesRec query_value_attribute(
                int target_type, 
                unsigned int attribute
            ) 
            {
                NVCTRLAttributeValidValuesRec value;

                bool error = XNVCTRLQueryValidTargetAttributeValues(
                    m_pDisplay,
                    target_type, 
                    m_gpu_id,
                    0, 
                    attribute,
                    &value
                );

                if (!error)
                    throw Kernel::Exceptions::Systems::Masters::GPUs::Nvidias::Error_Query_Value_Attribute(
                        target_type,
                        m_gpu_id,
                        attribute
                    );

                return value;
            }

            /**
             * @brief Set the int attribute
             * 
             * @param target_type What to set
             * @param attribute What attribute
             * @param value Value
             */
            void set_int_attribute(
                int target_type,
                unsigned int attribute,
                int value
            )
            {
                bool error = XNVCTRLSetTargetAttributeAndGetStatus(
                    m_pDisplay,
                    target_type,
                    m_gpu_id,
                    0, 
                    attribute,
                    value
                );

                if (!error)
                    throw Kernel::Exceptions::Systems::Masters::GPUs::Nvidias::Error_Set_Int_Attribute(
                        target_type,
                        m_gpu_id,
                        attribute
                    );
            }

        public:
            /**
             * @brief Construct a new gpu master nvidia object
             * 
             * @param gpu_id GPU ID
             */
            Nvidia(
                size_t gpu_id,
                Display *display
            ) : Systems::Masters::GPUs::Abstracts::GPU_Master_Abstract(
                    gpu_id
                ),
                m_pDisplay(
                    display
                )
            {
                NVCTRLAttributeValidValuesRec core, mem, voltage;

                int event_base, error_base;

                if (
                    !XNVCTRLQueryExtension(
                        m_pDisplay,
                        &event_base,
                        &error_base
                    )
                )
                    throw Kernel::Exceptions::Systems::Masters::GPUs::Nvidias::Error_XNVCtrl_Not_Found(
                        m_pDisplay
                    );

                nvmlDeviceGetHandleByIndex_v2(
                    m_gpu_id,
                    m_device
                );

                m_memory_usage_max = query_int_attribute(
                    NV_CTRL_TARGET_TYPE_GPU,
                    NV_CTRL_TOTAL_DEDICATED_GPU_MEMORY
                );
                voltage = query_value_attribute(
                    NV_CTRL_TARGET_TYPE_GPU,
                    NV_CTRL_GPU_OVER_VOLTAGE_OFFSET
                );
                core = query_value_attribute(
                    NV_CTRL_TARGET_TYPE_GPU,
                    NV_CTRL_GPU_NVCLOCK_OFFSET
                );
                mem = query_value_attribute(
                    NV_CTRL_TARGET_TYPE_GPU,
                    NV_CTRL_GPU_MEM_TRANSFER_RATE_OFFSET
                );

                m_power_usage_min = voltage.u.range.min;
                m_power_usage_max = voltage.u.range.max;
                m_core_clock_min = core.u.range.min;
                m_core_clock_max = core.u.range.max;
                m_mem_clock_min = mem.u.range.min;
                m_mem_clock_max = mem.u.range.max;
            }

            /**
             * @brief Destroy the gpu master nvidia object
             */
            virtual ~Nvidia() = default;

            /**
             * @brief Get the memory usage current object
             * 
             * @return size_t 
             */
            size_t get_memory_usage_current()
            {
                m_memory_usage_current = query_int_attribute(
                    NV_CTRL_TARGET_TYPE_GPU,
                    NV_CTRL_USED_DEDICATED_GPU_MEMORY
                );

                return m_memory_usage_current;
            }

            /**
             * @brief Get the power usage current object
             * 
             * @return size_t 
             */
            size_t get_power_usage_current()
            {
                m_power_usage_current = query_int_attribute(
                    NV_CTRL_TARGET_TYPE_GPU,
                    NV_CTRL_GPU_CURRENT_CORE_VOLTAGE
                );

                return m_power_usage_current;
            }

            /**
             * @brief Get the core clock current object
             * 
             * @return size_t 
             */
            size_t get_core_clock_current()
            {
                m_core_clock_current = query_int_attribute(
                    NV_CTRL_TARGET_TYPE_GPU,
                    NV_CTRL_GPU_CURRENT_CLOCK_FREQS
                );

                // The function returns a 32-bit packed, GPU clock is the upper 16
                m_core_clock_current = (m_core_clock_current & (0xFFFF << (32 - 16))) >> (32 - 16);

                return m_core_clock_current;
            }
            
            /**
             * @brief Get the fan speed current object
             * 
             * @return size_t 
             */
            size_t get_fan_speed_current()
            {
                m_fan_speed_current = query_int_attribute(
                    NV_CTRL_TARGET_TYPE_COOLER,
                    NV_CTRL_THERMAL_COOLER_CURRENT_LEVEL
                );

                return m_fan_speed_current;
            }
            
            /**
             * @brief Get the temp current object
             * 
             * @return size_t 
             */
            size_t get_temp_current()
            {
                m_temp_current = query_int_attribute(
                    NV_CTRL_TARGET_TYPE_THERMAL_SENSOR,
                    NV_CTRL_THERMAL_SENSOR_READING
                );

                return m_temp_current;
            }

            /**
             * @brief Get the mem clock current object
             * 
             * @return size_t 
             */
            size_t get_mem_clock_current()
            {
                m_core_clock_current = query_int_attribute(
                    NV_CTRL_TARGET_TYPE_GPU,
                    NV_CTRL_GPU_CURRENT_CLOCK_FREQS
                );

                // The function returns a 32-bit packed integer, Memory Clock lower 16
                m_core_clock_current = (m_mem_clock_current) & 0xFFFF;

                return m_core_clock_current;
            }

            /**
             * @brief Set the fan speed 
             * 
             * @param fan_speed Fan speed
             */
            void set_fan_speed_manual(size_t fan_speed)
            {
                set_int_attribute(
                    NV_CTRL_TARGET_TYPE_COOLER,
                    NV_CTRL_THERMAL_COOLER_LEVEL,
                    fan_speed
                );
            }

            /**
             * @brief Set the fan speed to auto mode
             */
            void set_fan_speed_auto()
            {
                int _ = query_int_attribute(
                    NV_CTRL_TARGET_TYPE_GPU,
                    NV_CTRL_GPU_COOLER_MANUAL_CONTROL
                );
            }

            /**
             * @brief Set the power usage object
             * 
             * @param power_usage Power usage
             */
            void set_power_usage(size_t power_usage)
            {
                set_int_attribute(
                    NV_CTRL_TARGET_TYPE_GPU,
                    NV_CTRL_GPU_OVER_VOLTAGE_OFFSET,
                    power_usage
                );
            }

            /**
             * @brief Set the power limit object
             * 
             * @param power_limit Power limit
             */
            void set_power_limit(size_t power_limit)
            {
                nvmlReturn_t ret = nvmlDeviceSetPowerManagementLimit(
                    *m_device,
                    power_limit
                );

                if (ret != NVML_SUCCESS)
                    throw Kernel::Exceptions::Systems::Masters::GPUs::Nvidias::Error_Set_Power_Limit(
                        m_device,
                        power_limit
                    );
            }

            /**
             * @brief Set the core clock object
             * 
             * @param core_clock Core clock
             */
            void set_core_clock(size_t core_clock)
            {
                set_int_attribute(
                    NV_CTRL_TARGET_TYPE_GPU,
                    NV_CTRL_GPU_NVCLOCK_OFFSET,
                    core_clock
                );
            }

            /**
             * @brief Set the memory clock object
             * 
             * @param mem_clock Memory clock
             */
            void set_mem_clock(size_t mem_clock)
            {
                set_int_attribute(
                    NV_CTRL_TARGET_TYPE_GPU,
                    NV_CTRL_GPU_MEM_TRANSFER_RATE_OFFSET,
                    mem_clock
                );
            }
    };

    /**
     * @brief AMD GPU communicator
     */
    class AMD :
        virtual public Systems::Masters::GPUs::Abstracts::GPU_Master_Abstract
    {
        private:

        public:
            AMD(
                size_t id
            ) : Systems::Masters::GPUs::Abstracts::GPU_Master_Abstract(
                    id
                )
            {
            }
    };
}

#endif