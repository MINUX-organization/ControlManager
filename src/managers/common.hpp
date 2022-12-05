/**
 * @file common.hpp
 * @author Daniil Ibragimov (ghaghal93@gmail.com)
 * @brief Common file for managers files
 * @version 0.1
 * @date 2022-11-10
 * 
 * @copyright Copyright (c) 2022
 */

#pragma once

#ifndef MANAGERS_COMMON_HEADER
#define MANAGERS_COMMON_HEADER

#include "../kernel/common.hpp"

#include "../base/utilities/commanders/inc/commanders.hpp"

namespace Managers::Abstracts
{
    class Manager_Abstract
    {
        private:

        protected:
            Base::Utilities::Commanders::Commander *m_pCommander;

        public:
            Manager_Abstract(
                Base::Utilities::Commanders::Commander *pCommander
            ) : m_pCommander(pCommander)
            {
            }

            virtual ~Manager_Abstract() = default;
    };
}

#endif