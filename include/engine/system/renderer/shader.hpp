#pragma once
#include "../src/engine/mhpch.cpp"
#include <glm/glm.hpp>


namespace MHelmet 
{
    class Shader
    {        
    public:
       // Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);
        Shader() = default;
        virtual ~Shader() = default;

        Shader(const Shader&) = default;
        Shader(Shader&&) = default;
        Shader& operator=(const Shader&) = default;
        Shader& operator=(Shader&&) = default;

        virtual void Bind() const   = 0;
        virtual void Unbind() const = 0;

        static RefCount<Shader>
        Create(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);
      /*  void SetUniform(const char* name, int value) const;
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
        uint32_t id_;*/
    };
}




