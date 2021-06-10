#pragma once

#include "geometry.hpp"

class Triangle final : public Geometry {
public:
    Triangle();
    //Triangle(/*float size*/);


    virtual float*  Positions() override;
    virtual uint32_t* Indices() override;

    virtual size_t SizePos() const override;
    virtual size_t SizeInd() const override;

private:
    float    m_Positions[9];
    uint32_t m_Indices[3];
    
};