#pragma once
#include "vbo.hpp"
#include "vbl.hpp"

namespace TFM_ECS {

class vao_t {

public:
	vao_t();
	~vao_t();

	vao_t(const vao_t&) = default;
	vao_t& operator=(const vao_t&) = default;

	vao_t(vao_t&&) noexcept = default;
	vao_t& operator=(vao_t&&) noexcept = default;

	void addBuffer(const vbo_t& VBO, const vbl_t& VBlayout);

	void bind()   const;
	void unbind() const;


private:

	uint32_t _VAO_ID { 0 };
	uint32_t _count{ 0 };


};}