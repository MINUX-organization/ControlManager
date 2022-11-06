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
#include <string>
#include <memory>
#include <cstdio>
#include <array>
#include <map>

using std::unique_ptr;
using std::string;
using std::array;
using std::cout;
using std::endl;
using std::map;
using json = nlohmann::json;

#endif