#pragma once
#include "engine/system/renderer/Renderer.hpp"


typedef unsigned int GLenum;

namespace MHelmet
{
    class OpenGLShader : public Shader
    {
        enum class Type
        {
            Shader,
            Program
        };
    
    public:
        OpenGLShader(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath, const std::string& geometryPath);
        OpenGLShader(const std::string& name, const std::string& GLSLFilePath);

        OpenGLShader() = default;
        virtual ~OpenGLShader();

        OpenGLShader(const OpenGLShader&) = default;
        OpenGLShader(OpenGLShader&&) = default;
        OpenGLShader& operator=(const OpenGLShader&) = default;
        OpenGLShader& operator=(OpenGLShader&&) = default;

        virtual void Bind()   const override;
        virtual void Unbind() const override;        

        virtual const std::string& GetName() const override;

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

        std::string LoadShader(const std::string& GLSLFilePath);
        std::unordered_map<GLenum, std::string> SplitGLSLFile(const std::string& GLSLSource);
        void CompileShader(const std::unordered_map<GLenum, std::string>& ShaderSources);

        static void CheckErrors(uint32_t OpenGLShader, Type type);

    private:
        uint32_t id_; 
        std::string m_Name;
        int m_Nshaders = 0;

    };
}