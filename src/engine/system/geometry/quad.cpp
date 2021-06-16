#include "engine/system/geometry/quad.hpp"
#include <vcruntime_string.h>

namespace MHelmet
{
    Quad::Quad(float size)
        : m_Size(size)
    {
        m_Vertices = 1 * 2 * 3;  // 1 face * 2 triangles * 3 vertices
        m_Elements = m_Vertices;

        const float half = m_Size / 2.0f;        

        float quad[32] =
        {
            // Positions          // UVS        // Normals
            -half, -half, 0.0f,   0.0f, 0.0f,   0.0f, 0.0f, 1.0f,
             half, -half, 0.0f,   1.0f, 0.0f,   0.0f, 0.0f, 1.0f,

            // Positions          // UVS        // Normals
             half,  half, 0.0f,   1.0f, 1.0f,   0.0f, 0.0f, 1.0f,
            -half,  half, 0.0f,   0.0f, 1.0f,   0.0f, 0.0f, 1.0f,
            
        };

        memcpy(m_Quad, quad, sizeof(quad));

        uint32_t indices[6] = { 0, 1, 2,    2, 3, 0 };

        memcpy(m_Indices, indices, sizeof(indices));       
    }

    float* Quad::GetModel()
    {
        return m_Quad;
    }

    uint32_t* Quad::Indices() { return m_Indices; }

    size_t Quad::Size() const { return sizeof(m_Quad); }

    uint32_t Quad::Count() const
    {
        return sizeof(m_Indices) / sizeof(uint32_t);
    }
}


