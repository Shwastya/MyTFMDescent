#pragma once

#include <cstdint>

//Attributes
//0 - positions
//1 - uvs
//2 - normals

class Geometry {
    public:
        Geometry() = default;
        virtual ~Geometry();

        Geometry(const Geometry&) = default;
        Geometry& operator=(const Geometry&) = default;

        Geometry(Geometry&&) noexcept = default;
        Geometry& operator=(Geometry&&) noexcept = default;

        virtual float*  Positions() = 0;
        virtual uint32_t* Indices() = 0;

        virtual size_t SizePos() const = 0;
        virtual size_t SizeInd() const = 0;
        //virtual float UVS()    const = 0;

    protected:       
        uint32_t m_Vertices = 0;
        uint32_t m_Elements = 0;

        


        

};
