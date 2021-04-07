#pragma once
#include "vbo.hpp"
#include "vbl.hpp"

namespace TFM_ECS {

class vao_t {

public:
	vao_t();
	~vao_t();

	void addBuffer(const vbo_t& VBO, const vbl_t& VBlayout);

	void bind()   const;
	void unbind() const;


private:

	uint32_t _VAO_ID { 0 };


};}