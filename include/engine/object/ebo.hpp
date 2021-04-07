#pragma once
#include <cstdint>

namespace TFM_ECS {

class ebo_t
{
public:

	ebo_t(const uint32_t* elementdata, const uint32_t nElements); // size sin usar
	~ebo_t();

	void bind()   const;
	void unbind() const;

	uint32_t getCount() const { return _nElements; }

private:

	uint32_t _EBO_ID { 0 };
	const uint32_t _nElements { 0 };
};

} 