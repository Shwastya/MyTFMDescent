#ifndef __CUBE_H__
#define __CUBE_H__ 1

#include "geometry.hpp"

class Cube final : public Geometry {
    public:
        Cube() = delete;
        explicit Cube(float size);

    private:
        const float _size = 0;
};
#endif