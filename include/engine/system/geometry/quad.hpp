#pragma once

#include "geometry.hpp"

namespace MHelmet
{
    class Quad final : public Geometry 
    {
    public:
        Quad() = delete;

        ~Quad()
        {
            delete[] m_VBO, m_Indices;
        }

        explicit Quad(float size);

        size_t SizeVBO()     { return m_VBOSize; }
        size_t SizeIndices() { return _nElements; }

        float* Get() { return m_VBO; }
        uint32_t* Indices() { return m_Indices; }       

    private:

        float* m_VBO;
        uint32_t* m_Indices;

        size_t m_VBOSize;        
    };
}

