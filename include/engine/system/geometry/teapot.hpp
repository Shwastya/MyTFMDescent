#pragma once

#include "geometry.hpp"

#include <glm/glm.hpp>

namespace MHelmet
{
    class Teapot final :public Geometry 
    {
    public:

        Teapot() = delete;
        
        ~Teapot() 
        {
            delete[] m_VBO, m_Indices;
        }

        explicit Teapot(uint32_t grid, glm::mat4 lidTransform = glm::mat4(1.0f));
        
        size_t SizeVBO() { return m_VBOSize; }
        size_t SizeIndices() { return _nElements; }

        float* Get() { return m_VBO; }
        uint32_t* Indices() { return m_Indices; }

        

    private:
        void generateVertexData(float* positions, float* uvs, float* normals, uint32_t* indices, uint32_t grid) const;

        static void buildPatchReflect(uint32_t patchNum, float* B, float* dB,
            float* positions, float* uvs, float* normals, uint32_t* indices,
            uint32_t& idx, uint32_t& uvIdx, uint32_t& indicesIdx, int grid,
            bool reflectX, bool reflectY);

        static void buildPatch(glm::vec3 patch[][4], float* B, float* dB,
            float* positions, float* uvs, float* normals, uint32_t* indices,
            uint32_t& idx, uint32_t& uvIdx, uint32_t& indicesIdx, uint32_t grid, glm::mat3 reflect,
            bool invertNormal);

        static glm::vec3 evaluate(int gridU, int gridV, float* B, glm::vec3 patch[][4]);
        static glm::vec3 evaluateNormal(int gridU, int gridV, float* B, float* dB, glm::vec3 patch[][4]);
        static void computeBasisFunctions(float* B, float* dB, uint32_t grid);
        static void getPatch(int patchNum, glm::vec3 patch[][4], bool reverseV);
        static void moveLid(int grid, float* positions, glm::mat4 lidTransform);

    private:

        float* m_VBO;
        uint32_t* m_Indices;

        size_t m_VBOSize;

        
    };
}


