#pragma once

#include <stdio.h>
#include <iostream> // std::cout
#include <fstream> // fstream
#include <sstream> // stringstream
#include <memory> // smart pointers
#include <vector>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "Tools.h"

// ImgGUI
#include "imgui.h"
#include "imgui_sdl.h"

// FMOD
#pragma warning(push)
#pragma warning(disable: 4505 26812)
#include "fmod.hpp" //Precompiled Header
#include "fmod_errors.h"
#pragma warning(pop)

#pragma comment(lib, "fmod_vc.lib")
#if defined(DEBUG) || defined(_DEBUG)
#pragma comment(lib, "fmodL_vc.lib")
#endif

// Editor
#define RunEditor