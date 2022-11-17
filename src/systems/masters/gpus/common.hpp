/**
 * @file common.hpp
 * @author Daniil Ibragimov (ghaghal93@gmail.com)
 * @brief Contains all abstract classes for GPU
 * @version 0.1
 * @date 2022-11-11
 * 
 * @copyright Copyright (c) 2022
 */

#pragma once

#ifndef SYSTEMS_OVERCLOCKS_COMMON_HEADER
#define SYSTEMS_OVERCLOCKS_COMMON_HEADER

#include "../common.hpp"

#include <X11/Xlib.h>

/**
 * @brief Contains all abstract classes for GPU communicators
 */
namespace Systems::GPU_Masters::Abstracts
{
    /**
     * @brief Abstract class for GPU communicator
     */
    class GPU_Master_Abstract
    {
        private:

        protected:
            /**
             * @brief Memory usage current (megabytes)
             */
            size_t m_memory_usage_current{ 0 };

            /**
             * @brief Power usage current
             */
            size_t m_power_usage_current{ 0 };

            /**
             * @brief Core clock current (MHz)
             */
            size_t m_core_clock_current{ 0 };

            /**
             * @brief Fan speed current (percentage)
             */
            size_t m_fan_speed_current{ 0 };

            /**
             * @brief Memory clock current (MHz)
             */
            size_t m_mem_clock_current{ 0 };

            /**
             * @brief Maximum available memory to use (megabyte)
             */
            size_t m_memory_usage_max{ 0 };

            /**
             * @brief Power usage maximum
             */
            size_t m_power_usage_max{ 0 };

            /**
             * @brief Power usage minimum
             */
            size_t m_power_usage_min{ 0 };

            /**
             * @brief Core clock maximum
             */
            size_t m_core_clock_max{ 0 };

            /**
             * @brief Core clock minimum
             */
            size_t m_core_clock_min{ 0 };

            /**
             * @brief Memory clock maximum
             */
            size_t m_mem_clock_max{ 0 };

            /**
             * @brief Memory clock minimum
             */
            size_t m_mem_clock_min{ 0 };

            /**
             * @brief Current temperature
             */
            size_t m_temp_current{ 0 };

            /**
             * @brief ID of GPU
             */
            size_t m_gpu_id{ 0 };

            /**
             * @brief Error handler for Xorg
             * 
             * @param display Display object
             * @param error Error value
             * @return int 
             */
            static int x_lib_error_handler(
                Display *display,
                XErrorEvent *error
            )
            {
                char buffer[5120];

                XGetErrorText(
                    display,
                    error->error_code,
                    buffer,
                    5120
                );

                return 0;
            }

        public:
            /**
             * @brief Construct a new gpu master abstract object
             * 
             * @param gpu_id ID of GPU
             */
            GPU_Master_Abstract(
                size_t gpu_id
            ) : m_gpu_id(gpu_id)
            {
                // Set error handler
                XSetErrorHandler(
                    &Systems::GPU_Masters::Abstracts::GPU_Master_Abstract::x_lib_error_handler
                );
            }

            /**
             * @brief Destroy the gpu master abstract object
             */
            virtual ~GPU_Master_Abstract() = default;

            /**
             * @brief Get the memory usage max object
             * 
             * @return size_t 
             */
            size_t get_memory_usage_max() { return m_memory_usage_max; }

            /**
             * @brief Get the power usage max object
             * 
             * @return size_t 
             */
            size_t get_power_usage_max() { return m_power_usage_max; }

            /**
             * @brief Get the power usage min object
             * 
             * @return size_t 
             */
            size_t get_power_usage_min() { return m_power_usage_min; }

            /**
             * @brief Get the core clock max object
             * 
             * @return size_t 
             */
            size_t get_core_clock_max() { return m_core_clock_max; }

            /**
             * @brief Get the core clock min object
             * 
             * @return size_t 
             */
            size_t get_core_clock_min() { return m_core_clock_min; }

            /**
             * @brief Get the memory clock max object
             * 
             * @return size_t 
             */
            size_t get_mem_clock_max() { return m_mem_clock_max; }

            /**
             * @brief Get the memory clock min object
             * 
             * @return size_t 
             */
            size_t get_mem_clock_min() { return m_mem_clock_min; }

            /**
             * @brief Get the gpu id object
             * 
             * @return size_t 
             */
            size_t get_gpu_id() { return m_gpu_id; }

            /**
             * @brief Get the memory usage current object
             * 
             * @return size_t 
             */
            virtual size_t get_memory_usage_current() = 0;

            /**
             * @brief Get the power usage current object
             * 
             * @return size_t 
             */
            virtual size_t get_power_usage_current() = 0;

            /**
             * @brief Get the core clock current object
             * 
             * @return size_t 
             */
            virtual size_t get_core_clock_current() = 0;

            /**
             * @brief Get the fan speed current object
             * 
             * @return size_t 
             */
            virtual size_t get_fan_speed_current() = 0;

            /**
             * @brief Get the memory clock current object
             * 
             * @return size_t 
             */
            virtual size_t get_mem_clock_current() = 0;

            /**
             * @brief Get the current temperature
             * 
             * @return size_t 
             */
            virtual size_t get_temp_current() = 0;

            /**
             * @brief Set the fan speed to manual value
             * 
             * @param fan_speed Fan speed percentage
             */
            virtual void set_fan_speed_manual(size_t fan_speed) = 0;

            /**
             * @brief Set the power usage
             * 
             * @param power_usage Power usage
             */
            virtual void set_power_usage(size_t power_usage) = 0;

            /**
             * @brief Set the power limit object
             * 
             * @param power_limit Power limit
             */
            virtual void set_power_limit(size_t power_limit) = 0;

            /**
             * @brief Set the core clock object
             * 
             * @param core_clock Core clock
             */
            virtual void set_core_clock(size_t core_clock) = 0;

            /**
             * @brief Set the memory clock 
             * 
             * @param mem_clock Memory clock
             */
            virtual void set_mem_clock(size_t mem_clock) = 0;

            /**
             * @brief Set the fan speed to auto mode
             */
            virtual void set_fan_speed_auto() = 0;

    };
}

#endif