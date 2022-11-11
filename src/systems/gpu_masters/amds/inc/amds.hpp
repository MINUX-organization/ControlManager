/**
 * @file amds.hpp
 * @author Daniil Ibragimov (ghaghal93@gmail.com)
 * @brief Contains masters for GPUs
 * @version 0.1
 * @date 2022-11-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#ifndef SYSTEMS_GPU_MASTERS_AMDS_HEADER
#define SYSTEMS_GPU_MASTERS_AMDS_HEADER

#include "../../common.hpp"

/**
 * @brief Contains classes to communicate with AMD GPUs
 */
namespace Systems::GPU_Masters::AMDs
{
    /**
     * @brief AMD GPU communicator
     */
    class GPU_Master_AMD :
        virtual public Systems::GPU_Masters::Abstracts::GPU_Master_Abstract
    {
        private:

        public:
            /**
             * @brief Construct a new gpu master amd object
             * 
             * @param gpu_id ID of GPU
             */
            GPU_Master_AMD(
                size_t gpu_id
            ) : Systems::GPU_Masters::Abstracts::GPU_Master_Abstract(
                    gpu_id
                )
            {
            }

            virtual ~GPU_Master_AMD() = default;
    };
}

#endif