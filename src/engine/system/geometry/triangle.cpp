#include "engine/system/geometry/triangle.hpp"

namespace MHelmet
{
    Triangle::Triangle()
    {
        _nVertices = 1 * 2 * 3;  //1 face * 2 triangles * 3 vertices
        _nElements = _nVertices;

        m_VBOSize = sizeof(float) * _nVertices * 3 +
            sizeof(float) * _nVertices * 2 +
            sizeof(float) * _nVertices * 3 +
            sizeof(float) * _nVertices * 3 +
            sizeof(float) * _nVertices * 3;

        m_VBO = new float[NV * 3 + NV * 2 + NV * 3 + NV * 3 + NV * 3];
        m_Indices = new uint32_t[sizeof(uint32_t) * _nElements];

        float positions[] = 
        {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.0f,  0.5f, 0.0f
        };

        float uvs[] = { 0.0f, 0.0f,
                        1.0f, 0.0f,
                        1.0f, 1.0f };

        float normals[] = { 0.0f, 0.0f, 1.0f,
                            0.0f, 0.0f, 1.0f,
                            0.0f, 0.0f, 1.0f, };

        for (size_t i = 0; i < 3; ++i) m_Indices[i] = i;

        setData(positions, uvs, normals, m_Indices, m_VBO, true);
    }
}
