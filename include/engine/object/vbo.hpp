#pragma once
#include <cstdint>

namespace TFM_ECS {

class vbo_t
{
public:

	vbo_t() = default;
	vbo_t(const void* data, const uint32_t nVertices); // size sin usar
	~vbo_t();

	vbo_t(const vbo_t&) = default;
	vbo_t& operator=(const vbo_t&) = default;

	vbo_t(vbo_t&&) noexcept = default;
	vbo_t& operator=(vbo_t&&) noexcept = default;

	void set(const void* data, const uint32_t nVertices);

	void bind()   const;
	void unbind() const;

private:

	int count { 0 };
	uint32_t _VBO_ID[5];
	uint32_t _nVertices { 0 };


};} // namespace TFM_ECS