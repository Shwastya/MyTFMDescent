#pragma once

#include "geometry.hpp"


namespace MHelmet
{
    class Cube final : public Geometry 
    {
    public:
        Cube() = delete;
        explicit Cube(float size);

        virtual float*   GetModel() override;
        virtual uint32_t* Indices() override;

        virtual size_t   Size()  const override;
        virtual uint32_t Count() const override;

    private:

        float    m_Size;
        float    m_Cube[288];
        uint32_t m_Indices[36];
    };
}


