/**
 * @file statistics.hpp
 * @author Daniil Ibragimov (ghaghal93@gmail.com)
 * @brief Contains statistic
 * @version 0.1
 * @date 2022-11-10
 * 
 * @copyright Copyright (c) 2022
 */

#pragma once

#ifndef MANAGERS_STATISTICS_HEADER
#define MANAGERS_STATISTICS_HEADER

#include "abstracts.hpp"

/**
 * @brief Contains statistic classes
 */
namespace Managers::Statistics
{
    /**
     * @brief Statistic object for hashrate
     */
    class Statistic_Hashrate : 
        virtual public Managers::Statistics::Abstracts::Statistic_Abstract
    {
        private:

        public:
            /**
             * @brief Construct a new Statistic_Hashrate object
             */
            Statistic_Hashrate(
            ) : Managers::Statistics::Abstracts::Statistic_Abstract(
                )
            {
            }

            /**
             * @brief Destroy the Statistic_Hashrate object
             */
            virtual ~Statistic_Hashrate() = default;

            string get_statistic()
            {
                return string("Hello statistic hashrate");
            }
    };

    /**
     * @brief Statistic object for temperature
     */
    class Statistic_Temperature :
        virtual public Managers::Statistics::Abstracts::Statistic_Abstract
    {
        private:

        public:
            /**
             * @brief Construct a new Statistic_Temperature object
             */
            Statistic_Temperature(
            ) : Managers::Statistics::Abstracts::Statistic_Abstract(
                )
            {
            }

            /**
             * @brief Destroy the Statistic_Temperature object
             */
            virtual ~Statistic_Temperature() = default;

            string get_statistic()
            {
                return string("Hello statistic temperature");
            }
    };
}

#endif