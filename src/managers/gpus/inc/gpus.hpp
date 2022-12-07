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

#include "../../../base/utilities/commanders/inc/commanders.hpp"

#include "../../../base/hardwares/gpus/inc/gpus.hpp"

/**
 * @brief Contains managers for GPUs
 */
namespace Managers::GPUs
{
    /**
     * @brief GPU manager
     */
    class GPU :
        virtual public Managers::Abstracts::Manager_Abstract
    {
        private:
            /**
             * @brief Xorg display object
             */
            Display *m_display = nullptr;

            /**
             * @brief Commander manager
             */
            Base::Utilities::Commanders::Commander *m_commander;

            /**
             * @brief Array of all Nvidia GPUs
             */
            vector<Base::Hardwares::GPUs::Nvidia*> m_nvidia_gpus;

            /**
             * @brief Array of all AMD GPUs
             */
            vector<Base::Hardwares::GPUs::AMD*> m_amd_gpus;

            void prepare_nvidia_gpus()
            {

            }

            void prepare_amd_gpus()
            {

            }

        protected:
            /**
             * @brief Construct a new gpu manager object
             */
            GPU(
                Base::Utilities::Commanders::Commander *pCommander,
                vector<Base::Hardwares::GPUs::Nvidia*> &nvidia_gpus,
                vector<Base::Hardwares::GPUs::AMD*> &amd_gpus
            ) : Managers::Abstracts::Manager_Abstract(
                    pCommander
                ),
                m_nvidia_gpus(
                    nvidia_gpus
                ),
                m_amd_gpus(
                    amd_gpus
                )
            {
                prepare_nvidia_gpus();
                prepare_amd_gpus();
            }

        public:
            /**
             * @brief Destroy the gpu manager object
             */
            virtual ~GPU() = default;

            static Managers::GPUs::GPU & get_instance(
                Base::Utilities::Commanders::Commander *pCommander,
                vector<Base::Hardwares::GPUs::Nvidia*> &nvidia_gpus,
                vector<Base::Hardwares::GPUs::AMD*> &amd_gpus
            )
            {
                static Managers::GPUs::GPU instance(
                    pCommander,
                    nvidia_gpus,
                    amd_gpus
                );

                return instance;
            }

            GPU(
                const Managers::GPUs::GPU&
            ) = delete;

            GPU(
                Managers::GPUs::GPU&&
            ) = delete;

            Managers::GPUs::GPU operator = (
                const Managers::GPUs::GPU&
            ) = delete;

            Managers::GPUs::GPU operator = (
                Managers::GPUs::GPU&&
            ) = delete;
    };
}

#endif