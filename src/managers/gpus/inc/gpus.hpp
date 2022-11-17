/**
 * @file gpus.hpp
 * @author Daniil Ibragimov (ghaghal93@gmail.com)
 * @brief Contains managers for GPUs
 * @version 0.1
 * @date 2022-11-10
 * 
 * @copyright Copyright (c) 2022
 */

#pragma once

#ifndef MANAGERS_GPUS_HEADER
#define MANAGERS_GPUS_HEADER

#include "../../common.hpp"

#include "../../../systems/masters/gpus/nvidias/inc/nvidias.hpp"
#include "../../../systems/masters/gpus/amds/inc/amds.hpp"

/**
 * @brief Contains managers for GPUs
 */
namespace Managers::GPUs
{
    /**
     * @brief GPU manager
     */
    class GPU_Manager
    {
        private:
            /**
             * @brief Array of all Nvidia GPUs
             */
            vector<Systems::GPU_Masters::Nvidias::GPU_Master_Nvidia> m_nvidia_gpus;

            /**
             * @brief Array of all AMD GPUs
             */
            vector<Systems::GPU_Masters::AMDs::GPU_Master_AMD> m_amd_gpus;

            /**
             * @brief Xorg display object
             */
            Display *m_display = nullptr;

        public:
            /**
             * @brief Construct a new gpu manager object
             */
            GPU_Manager()
            {
                bool error;

                int nvidia_gpus_count = 0;

                m_display = XOpenDisplay(nullptr);

                if (m_display == nullptr)
                    // TODO: Handle error
                    // Failed to open X display, check if $DISPLAY is set
                    exit(EXIT_FAILURE);

                // Initialize all Nvidia GPUs
                error = XNVCTRLQueryTargetCount(
                    m_display,
                    NV_CTRL_TARGET_TYPE_GPU,
                    &nvidia_gpus_count
                );
                
                if (!error)
                    // TODO: Handle error
                    // Failed to query amount of GPUs
                    exit(EXIT_FAILURE);

                for (int i = 0; i < nvidia_gpus_count; i++)
                    m_nvidia_gpus.push_back(
                        Systems::GPU_Masters::Nvidias::GPU_Master_Nvidia(
                            i,
                            m_display
                        )
                    );
            }

            /**
             * @brief Destroy the gpu manager object
             */
            virtual ~GPU_Manager() = default;

            
    };
}

#endif