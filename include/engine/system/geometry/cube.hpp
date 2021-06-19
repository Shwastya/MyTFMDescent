#pragma once

#include "geometry.hpp"


namespace MHelmet
{
    class Cube final : public Geometry 
    {
    public:
        Cube() = delete;
        explicit Cube(float size);

    private:
        float _size;
    };
}

