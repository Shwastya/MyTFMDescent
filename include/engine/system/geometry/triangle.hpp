#pragma once

#include "geometry.hpp"

namespace MHelmet
{
    class Triangle final : public Geometry
    {
    public:
        Triangle();

        virtual ~Triangle() { delete[] m_VBO, m_Indices; }

        size_t SizeVBO() { return m_VBOSize; }
        size_t SizeIndices() { return _nElements; }

        float* Get() { return m_VBO; }
        uint32_t* Indices() { return m_Indices; }

    private:

        float* m_VBO;
        uint32_t* m_Indices;

        size_t m_VBOSize;
    };
}
