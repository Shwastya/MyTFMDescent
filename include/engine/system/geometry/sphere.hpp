#pragma once

#include "geometry.hpp"

namespace MHelmet
{
    class Sphere final : public Geometry 
    {
    public:
        Sphere() = delete;

        ~Sphere() 
        {
            delete[] m_VBO, m_Indices;
        }

        Sphere(float radius, uint32_t stacks, uint32_t slices);
        
        size_t SizeVBO() { return m_VBOSize; }
        size_t SizeIndices() { return _nElements; }

        float* Get() { return m_VBO; }
        uint32_t* Indices() { return m_Indices; }

      

    private:
        void generateVertexData(float* positions, float* uvs, float* normals, uint32_t* indices) const;

    private:
        float _radius;
        uint32_t _stacks, _slices;

        uint32_t* m_Indices;
        float* m_VBO;

        size_t m_VBOSize;

        
    };
}



