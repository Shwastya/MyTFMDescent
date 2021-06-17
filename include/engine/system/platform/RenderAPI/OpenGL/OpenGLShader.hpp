#pragma once
#include "../src/engine/mhpch.cpp"
#include <glm/glm.hpp>

#include "engine/system/renderer/Renderer.hpp"



namespace MHelmet
{
    class OpenGLShader : public Shader
    {
        enum class Type
        {
            Vertex,
            Fragment,
            Geometry, // de momento es experimental y no se implementa
            Program
        };

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

        void CompileShader(const std::string& vertexCode, const std::string& fragmentCode);

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
        static void LoadShader(const char* path, std::string* code);      
        
        static void CheckErrors(uint32_t OpenGLShader, Type type);
        

        std::string FileToString(const std::string& GLSLFilePath);

    private:  
       // const std::string m_GLSL_Path;
        uint32_t id_;
    };
}




