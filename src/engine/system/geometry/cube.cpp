#include "engine/system/geometry/cube.hpp"
#include <vcruntime_string.h>

namespace MHelmet
{
    Cube::Cube(float size) : m_Size(size) 
    {
        m_Vertices = 6 * 2 * 3;   //6 faces * 2 triangles * 3 vertices;
        m_Elements = m_Vertices;

        const float half = size / 2.0f;

        float cube[288] = 
       { 
            //front
            
            // Positions            // UVS          // Normals
            -half, -half, half,     0.0f, 0.0f,     0.0f, 0.0f, 1.0f,
             half, -half, half,     1.0f, 0.0f,     0.0f, 0.0f, 1.0f,
             half,  half, half,     1.0f, 1.0f,     0.0f, 0.0f, 1.0f,

            -half, -half, half,     0.0f, 0.0f,     0.0f, 0.0f, 1.0f,
             half,  half, half,     1.0f, 1.0f,     0.0f, 0.0f, 1.0f,
            -half,  half, half,     0.0f, 1.0f,     0.0f, 0.0f, 1.0f,

             //right

             half, -half, half,     0.0f, 0.0f,     1.0f, 0.0f, 0.0f,
             half, -half,-half,     1.0f, 0.0f,     1.0f, 0.0f, 0.0f,
             half,  half,-half,     1.0f, 1.0f,     1.0f, 0.0f, 0.0f,

             half, -half, half,     0.0f, 0.0f,     1.0f, 0.0f, 0.0f,
             half,  half,-half,     1.0f, 1.0f,     1.0f, 0.0f, 0.0f,
             half,  half, half,     0.0f, 1.0f,     1.0f, 0.0f, 0.0f,

             //back

             half, -half, -half,    0.0f, 0.0f,     0.0f, 0.0f, -1.0f,
            -half, -half, -half,    1.0f, 0.0f,     0.0f, 0.0f, -1.0f,
            -half,  half, -half,    1.0f, 1.0f,     0.0f, 0.0f, -1.0f,

             half, -half, -half,    0.0f, 0.0f,     0.0f, 0.0f, -1.0f,
             -half, half, -half,    1.0f, 1.0f,     0.0f, 0.0f, -1.0f,
             half,  half, -half,    0.0f, 1.0f,     0.0f, 0.0f, -1.0f,

             //left

             -half, -half, -half,   0.0f, 0.0f,     -1.0f, 0.0f, 0.0f,
             -half, -half,  half,   1.0f, 0.0f,     -1.0f, 0.0f, 0.0f,
             -half,  half,  half,   1.0f, 1.0f,     -1.0f, 0.0f, 0.0f,

             -half, -half, -half,   0.0f, 0.0f,     -1.0f, 0.0f, 0.0f,
             -half,  half,  half,   1.0f, 1.0f,     -1.0f, 0.0f, 0.0f,
             -half,  half, -half,   0.0f, 1.0f,     -1.0f, 0.0f, 0.0f,

             //bottom

             -half, -half, -half,   0.0f, 0.0f,     0.0f, -1.0f, 0.0f,
              half, -half, -half,   1.0f, 0.0f,     0.0f, -1.0f, 0.0f,
              half, -half,  half,   1.0f, 1.0f,     0.0f, -1.0f, 0.0f,

             -half, -half, -half,   0.0f, 0.0f,     0.0f, -1.0f, 0.0f,
              half, -half,  half,   1.0f, 1.0f,     0.0f, -1.0f, 0.0f,
             -half, -half,  half,   0.0f, 1.0f,     0.0f, -1.0f, 0.0f,

             //top

             -half, half,   half,   0.0f, 0.0f,     0.0f, 1.0f, 0.0f,
              half, half,   half,   1.0f, 0.0f,     0.0f, 1.0f, 0.0f,
              half, half,  -half,   1.0f, 1.0f,     0.0f, 1.0f, 0.0f,

             -half, half,   half,   0.0f, 0.0f,     0.0f, 1.0f, 0.0f,
              half, half,  -half,   1.0f, 1.0f,     0.0f, 1.0f, 0.0f,
             -half, half,  -half,   0.0f, 1.0f,     0.0f, 1.0f, 0.0f,
        };

        memcpy(m_Cube, cube, sizeof(cube));

        uint32_t indices[36] = 
        { 
            0,  1,  2,      3,  4,  5,  // front
            6,  7,  8,      9,  10, 11, // right
            12, 13, 14,     15, 16, 17, // back
            18, 19, 20,     21, 22, 23, // left
            24, 25, 26,     27, 28, 29, // bottom
            30, 31, 32,     33, 34, 35  // top
        }; 

        memcpy(m_Indices, indices, sizeof(indices));       
    }

    float* Cube::GetModel()
    {
        return m_Cube;
    }

    uint32_t* Cube::Indices() { return m_Indices; }

    size_t Cube::Size() const { return sizeof(m_Cube); }


    uint32_t Cube::Count() const
    {
        return sizeof(m_Indices) / sizeof(uint32_t);
    }
}

