#pragma once

#include "geometry.hpp"

class Quad final: public Geometry {
    public:
        Quad() = delete;
        explicit Quad(float size);

    
        virtual float*  Positions() override;
        virtual uint32_t* Indices() override;

        virtual size_t SizePos() const override;
        virtual size_t SizeInd() const override;

    private:
        float _size;   
      
};
