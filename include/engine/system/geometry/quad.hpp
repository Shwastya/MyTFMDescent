#pragma once

#include "geometry.hpp"

namespace MHelmet
{
    class Quad final : public Geometry 
    {
    public:
        Quad() = delete;
        explicit Quad(float size);

    private:
        float _size;
    };
}

