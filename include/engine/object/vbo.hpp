#pragma once
#include <cstdint>

namespace TFM_ECS {

class vbo_t
{
public:

	vbo_t(const float* data, const uint32_t nVertices); // size sin usar
	~vbo_t();

	void bind()   const;
	void unbind() const;

private:

	uint32_t _VBO_ID { 0 };
	const uint32_t _nVertices { 0 };
};

} // namespace TFM_ECS