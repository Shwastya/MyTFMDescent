#pragma once

/* Import engine to projects */

#include "engine/engine.hpp"
//#include "engine/system/ImGui/ImGuiLayer.hpp"

/* INPUT System */
#include "engine/system/Input.hpp"
#include <MHkeyCodes.h>

/* For rendering */
#include "engine/system/renderer/Renderer.hpp"
#include "engine/system/renderer/RenderCommand.hpp"
#include "engine/system/renderer/VBO.hpp"
#include "engine/system/renderer/EBO.hpp"
#include "engine/system/platform/RenderAPI/OpenGL/OpenGLVBO.hpp";
#include "engine/system/platform/RenderAPI/OpenGL/OpenGLEBO.hpp";
#include "engine/system/renderer/shader.hpp" 
#include "engine/system/renderer/VAO.hpp"
#include "engine/system/renderer/PerspectiveCamera.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


