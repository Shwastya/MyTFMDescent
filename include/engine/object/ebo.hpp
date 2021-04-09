#pragma once
#include <cstdint>

namespace TFM_ECS {

class ebo_t
{
public:

	ebo_t() = default;
	ebo_t(const uint32_t* data, const uint32_t nElements); // size sin usar
	~ebo_t();

	ebo_t(const ebo_t&) = default;
	ebo_t& operator=(const ebo_t&) = default;

	ebo_t(ebo_t&&) noexcept = default;
	ebo_t& operator=(ebo_t&&) noexcept = default;

	void set(const uint32_t* elementdata, const uint32_t nElements);

	void bind()   const;
	void unbind() const;

	uint32_t getCount() const { return _nElements; }

private:

	uint32_t _EBO_ID { 0 };
	uint32_t _nElements { 0 };


};} 