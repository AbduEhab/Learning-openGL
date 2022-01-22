#pragma once

#include <glad/glad.h>
#include <iostream>
#include <unistd.h>
#include <fstream>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <map>
#include <unordered_map>
#include <string>
#include <vector>
#include <chrono>
#include <sstream>

#define FPS 60
#define FRAME_TIME_TARGET (1000.0f / FPS)

using Clock = std::chrono::high_resolution_clock;
using TimePoint = std::chrono::_V2::system_clock::time_point;

#ifdef DEBUG
#define Debug(x) x;
#define DebugPrint(x) \
    std::cout << (x) << std::endl
#endif // DEBUG

#ifdef NDEBUG
#define Debug(x) ;
#define DebugPrint(x) ;
#endif // NDEBUG

const std::string BINARY_DIRECTORY(std::string(get_current_dir_name()) + "/");