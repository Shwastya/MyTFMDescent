#pragma once

#include <cstdint>

#ifndef NV

#define NV static_cast<size_t>(_nVertices)
#endif // !NV

namespace MHelmet
{
    class Geometry
    {

    public:
        Geometry() = default;
        virtual ~Geometry() = default;

        Geometry(const Geometry&) = default;
        Geometry& operator=(const Geometry&) = default;

        Geometry(Geometry&&) noexcept = default;
        Geometry& operator=(Geometry&&) noexcept = default;
        
    protected:    

        void setData(const float* positions, const float* uvs,
            const float* normals, const uint32_t* indices, float* Spec_VBO, bool TangBitan = true);

        void calcTangents(const float* positions, const float* uvs,
            const float* normals, float* tangents, float* biTangents) const;

    protected:

        uint32_t _nVertices = 0;
        uint32_t _nElements = 0;
    };

}
