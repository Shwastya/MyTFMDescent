#include "engine/system/geometry/quad.hpp"
#include <vcruntime_string.h>



namespace MHelmet
{
    Quad::Quad(float size) 
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


        const float half = size / 2.0f;

        float positions[] = { half, half, 0.0f,    //upper right triangle
                              half, -half, 0.0f,
                              -half, half, 0.0f,

                              half, -half, 0.0f,   //lower left triangle
                              -half, half, 0.0f,
                              -half, -half, 0.0f };

        float uvs[] = { 1.0f, 1.0f,
                        1.0f, 0.0f,
                        0.0f, 1.0f,

                        1.0f, 0.0f,
                        0.0f, 1.0f,
                        0.0f, 0.0f };

        float normals[] = { 0.0f, 0.0f, 1.0f,
                            0.0f, 0.0f, 1.0f,
                            0.0f, 0.0f, 1.0f,

                            0.0f, 0.0f, 1.0f,
                            0.0f, 0.0f, 1.0f,
                            0.0f, 0.0f, 1.0f };

        uint32_t indices[] = { 0, 2, 1,
                               3 , 4, 5 };

        

        setData(positions, uvs, normals, indices, m_VBO, true);

        memcpy(m_Indices, indices, sizeof(indices));
    }
}
