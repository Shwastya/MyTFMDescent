#pragma once

#include "geometry.hpp"


namespace MHelmet
{
    class Cube final : public Geometry {
    public:
        Cube() = delete;
        explicit Cube(float size);

        virtual float*  Positions() override;
        virtual uint32_t* Indices() override;

    private:
        float _size;
    };
}


