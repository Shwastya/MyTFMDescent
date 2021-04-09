#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__ 1

#include <cstdint>

#include "engine/object/vbo.hpp"
#include "engine/object/ebo.hpp"
#include "engine/object/vao.hpp"
#include <glm/gtc/matrix_transform.hpp>
//#include <glm/vec3.hpp>
//#include <glm/vec2.hpp>
//Attributes
//0 - positions
//1 - uvs
//2 - normals

class Geometry 
{
public:
    Geometry() = default;
    virtual ~Geometry();

    Geometry(const Geometry&) = default;
    Geometry& operator=(const Geometry&) = default;

    Geometry(Geometry&&) noexcept = default;
    Geometry& operator=(Geometry&&) noexcept = default;

    virtual void render() const;

    using v2 = glm::vec2;
    using v3 = glm::vec3;

protected: // protected methods

    void uploadData(const float* positions, const float* uvs,
        const float* normals, const uint32_t* indices);

    void calcTangents(const float* positions, const float* uvs,
        const float* normals, float* tangents, float* biTangents) const;

protected: // protected attributes

    uint32_t _VAO = 0;
    uint32_t _VBO[6]{ 0,0,0,0,0,0 };

    uint32_t _nVertices = 0;
    uint32_t _nElements = 0;

private:   // private attributes
 
    TFM_ECS::vao_t VAO;
    TFM_ECS::vbo_t VBO;
    TFM_ECS::ebo_t EBO;
    TFM_ECS::vbl_t _layout;

   /* enum BufferObjectType
    {
        NONE = -1, POSITIONS = 0,
        UVS = 1, NORMALS = 2,
        TANGENTS = 3, BITANGENTS = 4
    };*/

};
#endif