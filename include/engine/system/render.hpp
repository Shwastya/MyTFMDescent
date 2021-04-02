#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdint>

namespace TFM_ECS {

class RenderSystem_t {

public:

	explicit RenderSystem_t(const uint32_t w, const uint32_t h, const char* t); 	
	~RenderSystem_t();

	/* RULE OF FIVE */
	RenderSystem_t(const RenderSystem_t&) = default;
   RenderSystem_t& operator=(const RenderSystem_t&) = default;
   RenderSystem_t(RenderSystem_t&&) noexcept = default;
   RenderSystem_t& operator=(RenderSystem_t&&) noexcept = default;
	/****************/
	
	/* EVENTS */
	// aqui iran los eventos de input entre otros
	/**********/

	uint32_t getWidth()  const;
	uint32_t getHeight() const;	

	void update() const;

	bool alive() const;
	void frame() const;

private:

	GLFWwindow* _window;

	const char* _title { "" };

	const uint32_t _width  { 0 };
	const uint32_t _height { 0 };
	
	};
	

} // namespace TFM_ECS