#pragma once

#include <glad/glad.h>
#include <iostream>

#include <fstream>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <map>
#include <unordered_map>
#include <string>
#include <vector>
#include <chrono>
#include <sstream>

#ifdef _WIN32

#include <windows.h>
#include <direct.h>

const std::string BINARY_DIRECTORY(_getcwd(NULL, 0));

//TCHAR buffer[MAX_PATH] = { 0 };
//GetModuleFileName(NULL, buffer, MAX_PATH);
//std::wstring::size_type pos = std::wstring(buffer).find_last_of(L"\\/");
//auto t = std::wstring(buffer).substr(0, pos);

#else

#include <unistd.h>
#include <filesystem>

const std::string BINARY_DIRECTORY(std::string((char*)std::filesystem::current_path().c_str()) + "/");
const std::string BINARY_DIRECTORY_TEST(std::string(get_current_dir_name()) + "/");

#endif

#define FPS 60
#define FRAME_TIME_TARGET (1000.0f / FPS)

using Clock = std::chrono::high_resolution_clock;
using TimePoint = std::chrono::system_clock::time_point;

#ifdef DEBUG
#define Debug(x) x;
#define DebugPrint(x) \
    std::cout << (x) << std::endl
#endif // DEBUG

#ifdef NDEBUG
#define Debug(x) ;
#define DebugPrint(x) ;
#endif // NDEBUG



