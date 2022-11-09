#pragma once

#ifndef SYSTEMS_OVERCLOCKS_COMMON_HEADER
#define SYSTEMS_OVERCLOCKS_COMMON_HEADER

#include "../common.hpp"

#include <X11/Xlib.h>
namespace Systems::GPU_Masters::Abstracts
{
    class GPU_Master_Abstract
    {
        private:

        protected:
            size_t m_memory_usage_current{ 0 };

            size_t m_power_usage_current{ 0 };

            size_t m_core_clock_current{ 0 };

            size_t m_fan_speed_current{ 0 };

            size_t m_mem_clock_current{ 0 };

            size_t m_memory_usage_max{ 0 };

            size_t m_power_usage_max{ 0 };

            size_t m_power_usage_min{ 0 };

            size_t m_core_clock_max{ 0 };

            size_t m_core_clock_min{ 0 };

            size_t m_mem_clock_max{ 0 };

            size_t m_mem_clock_min{ 0 };

            size_t m_temp_current{ 0 };

            size_t m_gpu_id{ 0 };

            Display *m_display = nullptr;

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
            GPU_Master_Abstract(
                size_t gpu_id
            ) : m_gpu_id(gpu_id)
            {
                m_display = XOpenDisplay(nullptr);
                if (m_display == nullptr)
                    // TODO: Handle error
                    // Failed to open X display, check if $DISPLAY is set
                    exit(EXIT_FAILURE);

                // Set error handler
                XSetErrorHandler(
                    &Systems::GPU_Masters::Abstracts::GPU_Master_Abstract::x_lib_error_handler
                );
            }

            virtual ~GPU_Master_Abstract() = default;

            size_t get_memory_usage_max() { return m_memory_usage_max; }

            size_t get_power_usage_max() { return m_power_usage_max; }

            size_t get_power_usage_min() { return m_power_usage_min; }

            size_t get_core_clock_max() { return m_core_clock_max; }

            size_t get_core_clock_min() { return m_core_clock_min; }

            size_t get_mem_clock_max() { return m_mem_clock_max; }

            size_t get_mem_clock_min() { return m_mem_clock_min; }

            size_t get_gpu_id() { return m_gpu_id; }

            virtual size_t get_memory_usage_current() = 0;

            virtual size_t get_power_usage_current() = 0;

            virtual size_t get_core_clock_current() = 0;

            virtual size_t get_fan_speed_current() = 0;

            virtual size_t get_mem_clock_current() = 0;

            virtual size_t get_temp_current() = 0;

            virtual void set_fan_speed_manual(size_t fan_speed) = 0;

            virtual void set_power_usage(size_t power_usage) = 0;

            virtual void set_power_limit(size_t power_limit) = 0;

            virtual void set_core_clock(size_t core_clock) = 0;

            virtual void set_mem_clock(size_t mem_clock) = 0;

            virtual void set_fan_speed_auto() = 0;

    };
}

#endif