extern "C" {
#include <glad/glad.h>
#include <string.h>
}
#include "engine/geometry/geometry.hpp"

//#include <glm/detail/func_geometric.inl>




Geometry::~Geometry() {
    //glDeleteBuffers(4, _VBO);
    //glDeleteVertexArrays(1, &_VAO);
}

void Geometry::calcTangents(const float* positions, const float* uvs, const float* normals, float* tangents, float* biTangents) const {
    for (size_t i = 0; i < _nVertices; i += 3) {
        const uint32_t idx3 = i * 3;
        const uint32_t idx2 = i * 2;

        glm::vec3 v0(positions[idx3 + 0], positions[idx3 + 1], positions[idx3 + 2]);
        glm::vec3 v1(positions[idx3 + 3], positions[idx3 + 4], positions[idx3 + 5]);
        glm::vec3 v2(positions[idx3 + 6], positions[idx3 + 7], positions[idx3 + 8]);

        glm::vec2 uv0(uvs[idx2 + 0], uvs[idx2 + 1]);
        glm::vec2 uv1(uvs[idx2 + 2], uvs[idx2 + 3]);
        glm::vec2 uv2(uvs[idx2 + 4], uvs[idx2 + 5]);

        glm::vec3 deltaPos1 = v1 - v0;
        glm::vec3 deltaPos2 = v2 - v0;

        glm::vec2 deltaUv1 = uv1 - uv0;
        glm::vec2 deltaUv2 = uv2 - uv0;

        float r = 1 / (deltaUv1.x * deltaUv2.y - deltaUv1.y * deltaUv2.x);
        glm::vec3 tangent = (deltaPos1 * deltaUv2.y - deltaPos2 * deltaUv1.y) * r;
        glm::vec3 biTangent = (deltaPos2 * deltaUv1.x - deltaPos1 * deltaUv2.x) * r;

        tangents[idx3 + 0] = tangents[idx3 + 3] = tangents[idx3 + 6] = tangent.x;
        tangents[idx3 + 1] = tangents[idx3 + 4] = tangents[idx3 + 7] = tangent.y;
        tangents[idx3 + 2] = tangents[idx3 + 5] = tangents[idx3 + 8] = tangent.z;

        biTangents[idx3 + 0] = biTangents[idx3 + 3] = biTangents[idx3 + 6] = biTangent.x;
        biTangents[idx3 + 1] = biTangents[idx3 + 4] = biTangents[idx3 + 7] = biTangent.y;
        biTangents[idx3 + 2] = biTangents[idx3 + 5] = biTangents[idx3 + 8] = biTangent.z;
    }

    for (size_t i = 0; i < _nVertices; ++i) {
        const uint32_t idx3 = i * 3;

        glm::vec3 n(normals[idx3 + 0], normals[idx3 + 1], normals[idx3 + 2]);
        glm::vec3 t(tangents[idx3 + 0], tangents[idx3 + 1], tangents[idx3 + 2]);
        glm::vec3 b(biTangents[idx3 + 0], biTangents[idx3 + 1], biTangents[idx3 + 2]);

        t = glm::normalize(t - n * glm::dot(t, n));

        if (glm::dot(glm::cross(n, t),b) < 0.0f) {
            t = t * -1.0f;
        }

        tangents[idx3 + 0] = t.x;
        tangents[idx3 + 1] = t.y;
        tangents[idx3 + 2] = t.z;
    }
}


void Geometry::uploadData(const float* positions, const float* uvs, const float* normals,
    const uint32_t* indices) {
    
    const size_t length    = static_cast<size_t>(_nVertices) * 3;
    const size_t uv_lenght = static_cast<size_t>(_nVertices) * 2;

    const auto tangents = new float[length];
    const auto biTangents = new float[length];

    int fileCount = 0;

    const auto data = new float[uv_lenght];

    glm::vec3 t1[5] = 
    {
        { 0.0f, 0.1f, 0.3f },
        { 0.3f, 0.1f, 0.3f },
        { 0.3f, 0.5f, 0.0f },
        { 0.3f, 0.5f, 0.0f },
        { 0.3f, 0.5f, 0.0f },
    };
    glm::vec3 t2[3] =
    {
        { 0.0f, 0.1f, 0.3f },
        { 0.3f, 0.1f, 0.3f },
        { 0.3f, 0.5f, 0.0f },       
    };

   
   // glm::vec3 t[10] = {t1 ,  }

  

    for (int i = 0; i < 5; ++i)
    {
        //std::cout << "{ " << t[i].x << ", " << t[i].y << ", " << t[i].z << " }" << std::endl;
    }
  

    for (size_t i = 0; i < length; ++i)
    {
        




        ++fileCount;
        if (fileCount == 3)
        {
            std::cout << std::endl;
            fileCount = 0;
        }
    
    }

   // memset(tangents, 0.0f, length * sizeof(float));
    //memset(biTangents, 0.0f, length * sizeof(float));

    calcTangents(positions, uvs, normals, tangents, biTangents);

  
 
   // std::cout << "length     : " << length << std::endl;


    //std::cout << "sizeof positions: " << sizeof(*positions)/sizeof(positions[0]) << std::endl;

    /*glGenVertexArrays(1, &_VAO);
    glGenBuffers(6, _VBO);

    glBindVertexArray(_VAO);*/


    
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _VBO[0]);         //elements
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * _nElements, indices, GL_STATIC_DRAW);
    const float half = 1 / 2.0f;
    float prueba[] = { -half, -half, half,    //front
                          half, -half, half,
                          half, half, half,

                          -half, -half, half,
                          half, half, half,
                          -half, half, half,

                          half, -half, half,    //right
                          half, -half, -half,
                          half, half, -half,

                          half, -half, half,
                          half, half, -half,
                          half, half, half,

                          half, -half, -half,    //back
                          -half, -half, -half,
                          -half, half, -half,

                          half, -half, -half,
                          -half, half, -half,
                          half, half, -half,

                          -half, -half, -half,    //left
                          -half, -half, half,
                          -half, half, half,

                          -half, -half, -half,
                          -half, half, half,
                          -half, half, -half,

                          -half, -half, -half,    //bottom
                          half, -half, -half,
                          half, -half, half,

                          -half, -half, -half,
                          half, -half, half,
                          -half, -half, half,

                          -half, half, half,    //top
                          half, half, half,
                          half, half, -half,

                          -half, half, half,
                          half, half, -half,
                          -half, half, -half,
                           0.0f, 0.0f,
                            1.0f, 0.0f,
                            1.0f, 1.0f,

                            0.0f, 0.0f,
                            1.0f, 1.0f,
                            0.0f, 1.0f,

                            //right
                            0.0f, 0.0f,
                            1.0f, 0.0f,
                            1.0f, 1.0f,

                            0.0f, 0.0f,
                            1.0f, 1.0f,
                            0.0f, 1.0f,

                            //back
                            0.0f, 0.0f,
                            1.0f, 0.0f,
                            1.0f, 1.0f,

                            0.0f, 0.0f,
                            1.0f, 1.0f,
                            0.0f, 1.0f,

                            //left
                            0.0f, 0.0f,
                            1.0f, 0.0f,
                            1.0f, 1.0f,

                            0.0f, 0.0f,
                            1.0f, 1.0f,
                            0.0f, 1.0f,

                            0.0f, 0.0f,   //bottom
                            1.0f, 0.0f,
                            1.0f, 1.0f,

                            0.0f, 0.0f,
                            1.0f, 1.0f,
                            0.0f, 1.0f,

                            0.0f, 0.0f,   //top
                            1.0f, 0.0f,
                            1.0f, 1.0f,

                            0.0f, 0.0f,
                            1.0f, 1.0f,
                            0.0f, 1.0f,

                        0.0f, 0.0f, 1.0f,  //front
                        0.0f, 0.0f, 1.0f,
                        0.0f, 0.0f, 1.0f,

                        0.0f, 0.0f, 1.0f,
                        0.0f, 0.0f, 1.0f,
                        0.0f, 0.0f, 1.0f,

                        1.0f, 0.0f, 0.0f,  //right
                        1.0f, 0.0f, 0.0f,
                        1.0f, 0.0f, 0.0f,

                        1.0f, 0.0f, 0.0f,
                        1.0f, 0.0f, 0.0f,
                        1.0f, 0.0f, 0.0f,

                        0.0f, 0.0f, -1.0f,  //back
                        0.0f, 0.0f, -1.0f,
                        0.0f, 0.0f, -1.0f,

                        0.0f, 0.0f, -1.0f,
                        0.0f, 0.0f, -1.0f,
                        0.0f, 0.0f, -1.0f,

                        -1.0f, 0.0f, 0.0f,  //left
                        -1.0f, 0.0f, 0.0f,
                        -1.0f, 0.0f, 0.0f,

                        -1.0f, 0.0f, 0.0f,
                        -1.0f, 0.0f, 0.0f,
                        -1.0f, 0.0f, 0.0f,

                        0.0f, -1.0f, 0.0f,  //bottom
                        0.0f, -1.0f, 0.0f,
                        0.0f, -1.0f, 0.0f,

                        0.0f, -1.0f, 0.0f,
                        0.0f, -1.0f, 0.0f,
                        0.0f, -1.0f, 0.0f,

                        0.0f, 1.0f, 0.0f,  //top
                        0.0f, 1.0f, 0.0f,
                        0.0f, 1.0f, 0.0f,

                        0.0f, 1.0f, 0.0f,
                        0.0f, 1.0f, 0.0f,
                        0.0f, 1.0f, 0.0f
    
    
    
    
    };

    EBO.set(indices, sizeof(uint32_t)* _nElements);
    VBO.set(prueba, sizeof(float) * _nVertices * 3);
    
    //glBindBuffer(GL_ARRAY_BUFFER, _VBO[1]);                 //positions
    //glBufferData(GL_ARRAY_BUFFER, sizeof(float) * _nVertices * 3, positions, GL_STATIC_DRAW);
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    //glEnableVertexAttribArray(0);

    //VBO.set(uvs, sizeof(float) * _nVertices * 2);
    
    //glBindBuffer(GL_ARRAY_BUFFER, _VBO[2]);                 //uvs
    //glBufferData(GL_ARRAY_BUFFER, sizeof(float) * _nVertices * 2, uvs, GL_STATIC_DRAW);
    //glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
    //glEnableVertexAttribArray(1);

    //VBO.set(normals, sizeof(float) * _nVertices * 3);
    
    //glBindBuffer(GL_ARRAY_BUFFER, _VBO[3]);                 //normals
    //glBufferData(GL_ARRAY_BUFFER, sizeof(float) * _nVertices * 3, normals, GL_STATIC_DRAW);
    //glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    //glEnableVertexAttribArray(2);

    //VBO.set(tangents, sizeof(float) * _nVertices * 3);
    
    //glBindBuffer(GL_ARRAY_BUFFER, _VBO[4]);                 //tangents
    //glBufferData(GL_ARRAY_BUFFER, sizeof(float) * _nVertices * 3, tangents, GL_STATIC_DRAW);
    //glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    //glEnableVertexAttribArray(3);

    //VBO.set(biTangents, sizeof(float) * _nVertices * 3);
    
    //glBindBuffer(GL_ARRAY_BUFFER, _VBO[5]);                 //bitangents
    //glBufferData(GL_ARRAY_BUFFER, sizeof(float) * _nVertices * 3, biTangents, GL_STATIC_DRAW);
    //glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    //glEnableVertexAttribArray(4);
    _layout.push<float>(3, "positions");
    _layout.push<float>(2, "uvs");
    _layout.push<float>(3, "normals");
    //_layout.push<float>(3, "tangents");
    //_layout.push<float>(3, "biTangents");
    VAO.addBuffer(VBO, _layout);

    


    //VBO.unbind();
    //glBindBuffer(GL_ARRAY_BUFFER, 0);
    EBO.bind();
    VAO.unbind();
    //glBindVertexArray(0);

    //EBO.unbind();
    //GLHE_(glBindBuffer(GL_ARRAY_BUFFER, 0));
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    

    delete[] tangents;
    delete[] biTangents;
}

void Geometry::render() const {

    //glBindVertexArray(_VAO);

    VAO.bind();
    
    glDrawElements(GL_TRIANGLES, _nElements, GL_UNSIGNED_INT, 0);
}