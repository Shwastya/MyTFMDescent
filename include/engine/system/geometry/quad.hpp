#pragma once

#include "geometry.hpp"

namespace MHelmet
{
    class Quad final : public Geometry 
    {
    public:

        Quad() = delete;
        explicit Quad(float size);


        virtual float*    GetModel() override;
        virtual uint32_t* Indices() override;

        virtual size_t   Size()  const override;
        virtual uint32_t Count() const override;

    private:

        float m_Size;
        float m_Quad[32];
        uint32_t m_Indices[6];
    };
}


