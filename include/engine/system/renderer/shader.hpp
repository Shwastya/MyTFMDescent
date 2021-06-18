#pragma once
#include <string>
#include "engine/system/utils/utils.hpp"


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

        virtual const std::string& GetName() const = 0;

        static RefCount<Shader> Create(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath, const std::string& geometryPath = "0");
        static RefCount<Shader> Create(const std::string& name, const std::string& GLSLFilePath);
       
    };    
}




