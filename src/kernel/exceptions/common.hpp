#pragma once

#ifndef KERNEL_EXCEPTIONS_COMMON_HEADER
#define KERNEL_EXCEPTIONS_COMMON_HEADER

#include "../common.hpp"

namespace Kernel::Exceptions::Abstracts
{
    class Exception_Abstract :
        public std::exception
    {
        private:

        protected:
            string m_message;

        public:
            Exception_Abstract() = default;

            virtual ~Exception_Abstract() = default;

            string what()
            {
                return m_message;
            }
    };
}

#endif