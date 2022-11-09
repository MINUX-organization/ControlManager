#pragma once

#ifndef SYSTEMS_GPU_MASTERS_NVIDIAS_HEADER
#define SYSTEMS_GPU_MASTERS_NVIDIAS_HEADER

#include "../../common.hpp"

#include <nvml.h>
#include <NVCtrl/NVCtrl.h>
#include <NVCtrl/NVCtrlLib.h>

namespace Systems::GPU_Masters::Nvidias
{
    class GPU_Master_Nvidia :
        virtual public Systems::GPU_Masters::Abstracts::GPU_Master_Abstract
    {
        private:
            nvmlDevice_t *m_device = new nvmlDevice_t;

            string query_string_attribute(
                int target_type,
                unsigned int attribute
            )
            {
                char *str;

                bool error = XNVCTRLQueryTargetStringAttribute(
                    m_display,
                    target_type,
                    m_gpu_id,
                    0,
                    attribute,
                    &str
                );

                if (!error)
                    // TODO: Handle error
                    exit(EXIT_FAILURE);
                
                return string(str);
            }

            int query_int_attribute(
                int target_type,
                unsigned int attribute
            )
            {
                int res;

                bool error = XNVCTRLQueryTargetAttribute(
                    m_display,
                    target_type,
                    m_gpu_id,
                    0,
                    attribute,
                    &res
                );

                if (!error)
                    // TODO: Handle error
                    exit(EXIT_FAILURE);

                return res;
            }

            NVCTRLAttributeValidValuesRec query_value_attribute(
                int target_type, 
                unsigned int attribute
            ) 
            {
                NVCTRLAttributeValidValuesRec value;

                bool error = XNVCTRLQueryValidTargetAttributeValues(
                    m_display,
                    target_type, 
                    m_gpu_id,
                    0, 
                    attribute,
                    &value
                );

                if (!error)
                    // TODO: Handle error
                    exit(EXIT_FAILURE);

                return value;
            }

            void set_int_attribute(
                int target_type,
                unsigned int attribute,
                int value
            )
            {
                bool error = XNVCTRLSetTargetAttributeAndGetStatus(
                    m_display,
                    target_type,
                    m_gpu_id,
                    0, 
                    attribute,
                    value
                );

                if (!error)
                    // TODO: Handle error
                    exit(EXIT_FAILURE);
            }

        public:
            GPU_Master_Nvidia(
                size_t gpu_id
            ) : Systems::GPU_Masters::Abstracts::GPU_Master_Abstract(
                    gpu_id
                )
            {
                NVCTRLAttributeValidValuesRec core, mem, voltage;

                nvmlDeviceGetHandleByIndex(
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

            virtual ~GPU_Master_Nvidia() = default;

            size_t get_memory_usage_current()
            {
                m_memory_usage_current = query_int_attribute(
                    NV_CTRL_TARGET_TYPE_GPU,
                    NV_CTRL_USED_DEDICATED_GPU_MEMORY
                );

                return m_memory_usage_current;
            }

            size_t get_power_usage_current()
            {
                m_power_usage_current = query_int_attribute(
                    NV_CTRL_TARGET_TYPE_GPU,
                    NV_CTRL_GPU_CURRENT_CORE_VOLTAGE
                );

                return m_power_usage_current;
            }

            size_t get_core_clock_current()
            {
                m_core_clock_current = query_int_attribute(
                    NV_CTRL_TARGET_TYPE_GPU,
                    NV_CTRL_GPU_CURRENT_CLOCK_FREQS
                );

                // The function returns a 32-bit packed, GPU clock is the upper 16
                m_core_clock_current = (m_core_clock_current & (0xFFFF << (32 - 16))) >> (32 - 16);
            }
            
            size_t get_fan_speed_current()
            {
                m_fan_speed_current = query_int_attribute(
                    NV_CTRL_TARGET_TYPE_COOLER,
                    NV_CTRL_THERMAL_COOLER_CURRENT_LEVEL
                );

                return m_fan_speed_current;
            }
            
            size_t get_temp_current()
            {
                m_temp_current = query_int_attribute(
                    NV_CTRL_TARGET_TYPE_THERMAL_SENSOR,
                    NV_CTRL_THERMAL_SENSOR_READING
                );

                return m_temp_current;
            }

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

            void set_fan_speed_manual(size_t fan_speed)
            {
                set_int_attribute(
                    NV_CTRL_TARGET_TYPE_COOLER,
                    NV_CTRL_THERMAL_COOLER_LEVEL,
                    fan_speed
                );
            }

            void set_fan_speed_auto()
            {
                int _ = query_int_attribute(
                    NV_CTRL_TARGET_TYPE_GPU,
                    NV_CTRL_GPU_COOLER_MANUAL_CONTROL
                );
            }

            void set_power_usage(size_t power_usage)
            {
                set_int_attribute(
                    NV_CTRL_TARGET_TYPE_GPU,
                    NV_CTRL_GPU_OVER_VOLTAGE_OFFSET,
                    power_usage
                );
            }

            void set_power_limit(size_t power_limit)
            {
                nvmlReturn_t ret = nvmlDeviceSetPowerManagementLimit(
                    *m_device,
                    power_limit
                );

                if (ret != NVML_SUCCESS)
                    // TODO: Handle error
                    exit(EXIT_FAILURE);
            }

            void set_core_clock(size_t core_clock)
            {
                set_int_attribute(
                    NV_CTRL_TARGET_TYPE_GPU,
                    NV_CTRL_GPU_NVCLOCK_OFFSET,
                    core_clock
                );
            }

            void set_mem_clock(size_t mem_clock)
            {
                set_int_attribute(
                    NV_CTRL_TARGET_TYPE_GPU,
                    NV_CTRL_GPU_MEM_TRANSFER_RATE_OFFSET,
                    mem_clock
                );
            }
    };
}

#endif