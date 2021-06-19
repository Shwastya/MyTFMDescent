#pragma once

#include "geometry.hpp"
#include <vector>

namespace MHelmet
{
    class Sphere final : public Geometry {
    public:
        Sphere() = delete;
        Sphere(float radius, uint32_t stacks, uint32_t slices);
;

    private:
        void generateVertexData(float* positions, float* uvs, float* normals, uint32_t* indices) const;

    private:
        float _radius;
        uint32_t _stacks, _slices;
    };
}



