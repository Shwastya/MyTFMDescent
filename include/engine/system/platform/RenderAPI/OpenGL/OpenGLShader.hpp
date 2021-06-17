#pragma once
#include "../src/engine/mhpch.cpp"
#include <glm/glm.hpp>

#include "engine/system/renderer/Renderer.hpp"

#include <unordered_map>

namespace MHelmet
{
    enum class Type
    {
        Vertex,
        Fragment,
        Geometry, // de momento es experimental y no se implementa
        Program
    };

    struct ShaderTypesMap
    {
        Type type;
        std::string code;
    };


    class OpenGLShader : public Shader
    {      

    public:
        OpenGLShader(const std::string& vertexPath, const std::string& fragmentPath);
        OpenGLShader(const std::string& GLSLFilePath);
        
        OpenGLShader() = default;
        virtual ~OpenGLShader();

        OpenGLShader(const OpenGLShader&) = default;
        OpenGLShader(OpenGLShader&&) = default;
        OpenGLShader& operator=(const OpenGLShader&) = default;
        OpenGLShader& operator=(OpenGLShader&&) = default;

        virtual void Bind()   const override;
        virtual void Unbind() const override;

        

        // Overload set uniforms functions
        void Uniform(const char* name, int value) const;
        void Uniform(const char* name, float value) const;
        void Uniform(const char* name, bool value) const;
        void Uniform(const char* name, float value1, float value2) const;
        void Uniform(const char* name, float value1, float value2, float value3) const;
        void Uniform(const char* name, float value1, float value2, float value3, float value4) const;
        void Uniform(const char* name, const glm::vec2& value) const;
        void Uniform(const char* name, const glm::vec3& value) const;
        void Uniform(const char* name, const glm::vec4& value) const;
        void Uniform(const char* name, const glm::mat2& value) const;
        void Uniform(const char* name, const glm::mat3& value) const;
        void Uniform(const char* name, const glm::mat4& value) const;

    private:
        std::string LoadShaderFromString(const std::string& GLSLFilePath);
        static void LoadShaderFromChar(const char* path, std::string* code);    

        ShaderTypesMap SplitGlslSource(const std::string& GLSLSource);
        void Compile(const ShaderTypesMap& ShaderSrc);


        void CompileShader(const std::string& vertexCode, const std::string& fragmentCode);
        static void CheckErrors(uint32_t OpenGLShader, Type type);        

    private:  
       // const std::string m_GLSL_Path;
        uint32_t id_;
    };
}