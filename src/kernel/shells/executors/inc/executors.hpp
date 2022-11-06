#pragma once

#ifndef KERNEL_SHELL_EXECUTOR_HEADER
#define KERNEL_SHELL_EXECUTOR_HEADER

#include "../../../common.hpp"

#include "../../commands/inc/commands.hpp"

namespace Kernel::Shells::Executors
{
    class Executor
    {
        private:
            string m_result;

        public:
            Executor() = default;

            ~Executor() = default;

            void execute(
                Kernel::Shells::Commands::Command &command
            )
            {
                string cmd = command.get_command();

                char buffer[1024];

                m_result = "";

                FILE* pipe = popen(
                    cmd.c_str(),
                    "r"
                );

                while(!feof(pipe))
                    if(fgets(buffer, 1024, pipe) != NULL)
                        m_result += buffer;

                pclose(pipe);
            }

            string get_result()
            {
                return m_result;
            }
    };
}







#endif