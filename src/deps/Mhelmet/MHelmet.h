#pragma once

/* Import engine to projects */

#include "engine/engine.hpp"
//#include "engine/system/ImGui/ImGuiLayer.hpp"

/* INPUT System */
#include "engine/system/Input.hpp"
#include <MHkeyCodes.h>

/* For rendering */
#include "engine/system/renderer/Renderer.hpp"
#include "engine/system/renderer/RenderDrawCall.hpp"
#include "engine/system/renderer/VBO.hpp"
#include "engine/system/renderer/EBO.hpp"
#include "engine/system/platform/RenderAPI/OpenGL/OpenGLVBO.hpp";
#include "engine/system/platform/RenderAPI/OpenGL/OpenGLEBO.hpp";

#include "engine/system/renderer/VAO.hpp"
//#include "engine/system/renderer/PerspectiveCamera.hpp"
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
#include "engine/system/utils/Descompose.hpp"


//#include "engine/system/renderer/Texture.hpp"
#include "engine/system/renderer/FrameBuffer.hpp"

/* DE momento super cutrisiiiimo para facilitar un poco el tema */
#include "engine/system/utils/Library.hpp"

/* Geometries manager */
#include "engine/system/renderer/RendererGeometry.hpp"
//#include "engine/system/geometry/triangle.hpp"
//#include "engine/system/geometry/quad.hpp"
//#include "engine/system/geometry/cube.hpp"
//#include "engine/system/geometry/sphere.hpp"
//#include "engine/system/geometry/teapot.hpp"

#include "engine/system/scene/Entity.hpp"


/* No muy seguro de que sea el mejor lugar */

struct ModelTransform
{
	glm::vec3 Translate = glm::vec3(1.0f);
	glm::vec3 Rotate = glm::vec3(1.0f);
	float Degrees = 0.0f;
	glm::vec3 Scale = glm::vec3(1.0f);

};


