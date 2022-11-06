#pragma once

#ifndef KERNEL_COMMON_HEADER
#define KERNEL_COMMON_HEADER

#include <nlohmann/json.hpp>
#include <algorithm>
#include <pthread.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <fstream>
#include <string>
#include <memory>
#include <cstdio>
#include <chrono>
#include <vector>
#include <thread>
#include <array>
#include <map>


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