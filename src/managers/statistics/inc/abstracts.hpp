/**
 * @file abstracts.hpp
 * @author Daniil Ibragimov (ghaghal93@gmail.com)
 * @brief Contains abstract classes for statistic
 * @version 0.1
 * @date 2022-11-10
 * 
 * @copyright Copyright (c) 2022
 */

#pragma once

#ifndef MANAGERS_STATISTICS_ABSTRACTS_HEADER
#define MANAGERS_STATISTICS_ABSTRACTS_HEADER

#include "../../common.hpp"

/**
 * @brief Contains abstract classes for statistics
 */
namespace Managers::Statistics::Abstracts
{
    /**
     * @brief Abstract class for statistic
     */
    class Statistic_Abstract
    {
        private:

        protected:

        public:
            /**
             * @brief Construct a new Statistic_Abstract object
             */
            Statistic_Abstract() = default;

            /**
             * @brief Destroy the Statistic_Abstract object
             */
            virtual ~Statistic_Abstract() = default;
    };
}

#endif