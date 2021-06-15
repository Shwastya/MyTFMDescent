#pragma once
#//include <cstdint>
#include "engine/system/renderer/shader.hpp"
#include <glm/glm.hpp>



namespace MHelmet
{
    class OpenGLShader : public Shader
    {
        enum class Type
        {
            Vertex,
            Fragment,
            Geometry,
            Program
        };

    public:
        OpenGLShader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);
        OpenGLShader() = default;
        virtual ~OpenGLShader();

        OpenGLShader(const OpenGLShader&) = default;
        OpenGLShader(OpenGLShader&&) = default;
        OpenGLShader& operator=(const OpenGLShader&) = default;
        OpenGLShader& operator=(OpenGLShader&&) = default;

        void Bind()   const override;
        void Unbind() const override;

        void SetUniform(const char* name, int value) const;
        void SetUniform(const char* name, float value) const;
        void SetUniform(const char* name, bool value) const;
        void SetUniform(const char* name, float value1, float value2) const;
        void SetUniform(const char* name, float value1, float value2, float value3) const;
        void SetUniform(const char* name, float value1, float value2, float value3, float value4) const;
        void SetUniform(const char* name, const glm::vec2& value) const;
        void SetUniform(const char* name, const glm::vec3& value) const;
        void SetUniform(const char* name, const glm::vec4& value) const;
        void SetUniform(const char* name, const glm::mat2& value) const;
        void SetUniform(const char* name, const glm::mat3& value) const;
        void SetUniform(const char* name, const glm::mat4& value) const;

    private:
        static void loadShader(const char* path, std::string* code);
        static void checkErrors(uint32_t shader, Type type);
        uint32_t id_;
    };
}