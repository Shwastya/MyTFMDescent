#pragma once

/* Future Work - defines for different platforms */
#include <Windows.h>
/*************************************************/

#include <iostream>
#include <cstdint>
#include <memory>
#include <vector>
#include <string>
#include <array>
#include <unordered_map>
#include <functional>
#include <algorithm>

#include <fstream>

#include "engine/system/events/Event.hpp"
#include "engine/system/events/EventSender.hpp"

/* ImGui System */

// las cabeceras imgui estan ahora mismo mal distribuidas
// demasiado redundantes en principio deberia dejar solo #include <imgui.h>
#include <imgui.h>
//#include <imgui_impl_glfw.h>
//#include <imgui_impl_opengl3.h>

/* Delta Time */
#include "engine/system/utils/utils.hpp"




