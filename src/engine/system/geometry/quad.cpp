#include "engine/system/geometry/quad.hpp"

namespace MHelmet
{
    Quad::Quad(float size)
        : _size(size)
    {
        m_Vertices = 1 * 2 * 3;  // 1 face * 2 triangles * 3 vertices
        m_Elements = m_Vertices;

        const float half = _size / 2.0f;

        float positions[18] =
        {
            half, half, 0.0f,    //upper right triangle
            half, -half, 0.0f,
            -half, half, 0.0f,

            half, -half, 0.0f,   //lower left triangle
            -half, half, 0.0f,
            -half, -half, 0.0f
        };

        // memcpy(m_p)

        float uvs[] =
        {
            1.0f, 1.0f,
            1.0f, 0.0f,
            0.0f, 1.0f,

            1.0f, 0.0f,
            0.0f, 1.0f,
            0.0f, 0.0f
        };

        float normals[] =
        {
            0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f,

            0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f
        };

        uint32_t indices[] =
        {
            0, 2, 1,
            3 , 4, 5
        };
    }

    float* Quad::Positions()
    {
        const float half = _size / 2.0f;

        float positions[18] =
        {
            half, half, 0.0f,    //upper right triangle
            half, -half, 0.0f,
            -half, half, 0.0f,

            half, -half, 0.0f,   //lower left triangle
            -half, half, 0.0f,
            -half, -half, 0.0f
        };



        return positions;
    }

    uint32_t* Quad::Indices()
    {
        return uint32_t();
    }

    size_t Quad::Size() const
    {
        return 0;
    }

    uint32_t Quad::Count() const
    {
        return uint32_t();
    }
}


