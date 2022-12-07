/**
 * @file executors.hpp
 * @author Daniil Ibragimov (ghaghal93@gmail.com)
 * @brief Contains executors for commands
 * @version 0.1
 * @date 2022-11-10
 * 
 * @copyright Copyright (c) 2022
 */

#pragma once

#ifndef SYSTEMS_SHELL_EXECUTOR_HEADER
#define SYSTEMS_SHELL_EXECUTOR_HEADER

#include "../../common.hpp"

#include "../../commands/inc/commands.hpp"

/**
 * @brief Contains executors for commands
 */
namespace Systems::Shells::Executors
{
    /**
     * @brief Command executor
     */
    class Executor
    {
        private:
            /**
             * @brief Result of command execution
             */
            string m_result;

        public:
            /**
             * @brief Construct a new Executor object
             */
            Executor() = default;

            /**
             * @brief Destroy the Executor object
             */
            ~Executor() = default;

            /**
             * @brief Execute command
             * 
             * @param command Command object
             */
            void execute(
                Systems::Shells::Commands::Abstracts::Command_Information_Abstract *command
            )
            {
                string cmd = command->get_command();

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

            /**
             * @brief Get the result of last command
             * 
             * @return string 
             */
            string get_result()
            {
                return m_result;
            }
    };
}







#endif