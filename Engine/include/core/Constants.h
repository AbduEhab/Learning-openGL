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

const std::string BINARY_DIRECTORY(std::string(_getcwd(NULL, 0)) + '/');

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

#define _unlikely [[UNLIKELY]]

#define FPS 60
#define FRAME_TIME_TARGET (1000.0f / FPS)

using Clock = std::chrono::high_resolution_clock;
using TimePoint = std::chrono::system_clock::time_point;

#define TUNA_SHADER_PATH "Engine/shaders/"

#define TUNA_SHADER_VERTEX_EXTENSION ".vert"
#define TUNA_SHADER_FRAGMENT_EXTENSION ".frag"

//print multiple variables
#define PRINT_VAR(...) printf(__VA_ARGS__)

//print multiple variables with new line
#define PRINT_VAR_NL(...) printf(__VA_ARGS__); printf("\n")

//print multiple variables with new line and flush
#define PRINT_VAR_NL_FLUSH(...) printf(__VA_ARGS__); printf("\n"); fflush(stdout)

#ifdef DEBUG
#define Debug(x) x;

//print multiple variables
#define PRINT_VAR(...) printf(__VA_ARGS__)

//print multiple variables with new line
#define PRINT_VAR_NL(...) printf(__VA_ARGS__); printf("\n")

//print multiple variables with new line and flush
#define PRINT_VAR_NL_FLUSH(...) printf(__VA_ARGS__); printf("\n"); fflush(stdout)

#endif // DEBUG

#ifdef NDEBUG
#define Debug(x) ;

//print multiple variables
#define PRINT_VAR(...) ;

//print multiple variables with new line
#define PRINT_VAR_NL(...) ;

//print multiple variables with new line and flush
#define PRINT_VAR_NL_FLUSH(...) ;

#endif // NDEBUG



