#pragma once
#include "../src/engine/mhpch.cpp"
#include <glm/glm.hpp>

namespace MHelmet 
{
    class Shader
    {        
    public:

        Shader() = default;
        virtual ~Shader() = default;

        Shader(const Shader&) = default;
        Shader(Shader&&) = default;
        Shader& operator=(const Shader&) = default;
        Shader& operator=(Shader&&) = default;

        virtual void Bind() const   = 0;
        virtual void Unbind() const = 0;

        static RefCount<Shader> Create(const std::string& vertexPath, const std::string& fragmentPath);
        static RefCount<Shader> Create(const std::string& GLSLFilePath);
       
    };

    class ShaderLib
    {

    };
}




