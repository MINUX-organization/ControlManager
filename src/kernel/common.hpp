/**
 * @file common.hpp
 * @author Daniil Ibragimov (ghaghal93@gmail.com)
 * @brief Common file for kernel files
 * @version 0.1
 * @date 2022-11-10
 * 
 * @copyright Copyright (c) 2022
 */

#pragma once

#ifndef KERNEL_COMMON_HEADER
#define KERNEL_COMMON_HEADER

#include <boost/bind/bind.hpp>
#include <boost/signals2.hpp>

#include <nlohmann/json.hpp>

#include <algorithm>
#include <iostream>
#include <fstream>
#include <csignal>
#include <string>
#include <memory>
#include <cstdio>
#include <chrono>
#include <vector>
#include <thread>
#include <future>
#include <mutex>
#include <array>
#include <map>

#include <signal.h>
#include <errno.h>

#include <sys/select.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

using json = nlohmann::json;

using std::this_thread::sleep_for;
using std::chrono::milliseconds;
using std::unique_ptr;
using std::ifstream;
using std::vector;
using std::string;
using std::array;
using std::cout;
using std::endl;
using std::map;

#endif