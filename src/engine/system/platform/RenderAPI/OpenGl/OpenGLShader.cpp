#include "engine/system/MHCore.hpp"
#include "engine/system/platform/RenderAPI/OpenGL/OpenGLShader.hpp"
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <sstream>

namespace MHelmet
{
    OpenGLShader::OpenGLShader(const std::string& vertexPath, const std::string& fragmentPath)
    {
        std::string vertexCode, fragmentCode;

        LoadShader(vertexPath.c_str(), &vertexCode);
        LoadShader(fragmentPath.c_str(), &fragmentCode);
        CompileShader(vertexCode, fragmentCode);
    }

    OpenGLShader::OpenGLShader(const std::string& GLSLFile) //: m_GLSL_Path(GLSLFile)
    {
        // file system es muy complejo entre plataformas
        // en este punto pongo un recordatorio:
        // si se quiere extender el modelo e implementar 
        // en otras plataformas, habria que aumentar el nivel
        // de abstraccion del file system para que funcionara 
        // correctamente en multiplataforma      

        std::string ShaderSrc = FileToString(GLSLFile);
        
        std::string vertexCode, fragmentCode;

        const char* token = "#TYPE";
        size_t tokenLenght = strlen(token);
        size_t pos = ShaderSrc.find(token, 0);
      
        // La siguiente seccion de codigo habria que mejorar mucho la abstraccion
        // De momento, por las prisas, siendo funcional, lo dejo asi
     
        // NO TIENE CONTROL DE ERRORES !!!!!!!!!!
        // MUCHO CUIDADO AL ESCRIBIR LOS SHADERS !!!!!!!!
        while (pos != std::string::npos)
        {
            size_t eol = ShaderSrc.find_first_of("\r\n", pos);

            size_t begin = pos + tokenLenght + 1;
            std::string type = ShaderSrc.substr(begin, eol - begin);           

            size_t nextLinePos = ShaderSrc.find_first_not_of("\r\n", eol);
            pos = ShaderSrc.find(token, nextLinePos);            

            if (type == "VERTEX")            
                vertexCode = ShaderSrc.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? ShaderSrc.size() - 1 : nextLinePos));
            
            if (type == "FRAGMENT")            
                fragmentCode = ShaderSrc.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? GLSLFile.size() - 1 : nextLinePos));                        
        }


        CompileShader(vertexCode, fragmentCode);
    }


    OpenGLShader::~OpenGLShader()
    {
        glDeleteProgram(id_);
    }

    void OpenGLShader::Bind() const
    {
        glUseProgram(id_);
    }

    void OpenGLShader::Unbind() const
    {
        glUseProgram(0);
    }

    void OpenGLShader::LoadShader(const char* path, std::string* code)
    {
        std::ifstream file;

        file.open(path, std::ios_base::in);
        if (file)
        {
            std::stringstream stream;
            stream << file.rdbuf();
            *code = stream.str();
            file.close();
        }
        else CORE_ERROR("Error in load shader: {0}", path);
    }

    void OpenGLShader::CompileShader(const std::string& vertexCode, const std::string& fragmentCode)
    {
        const char* vertexStr = vertexCode.c_str();
        const uint32_t vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vertexStr, nullptr);
        glCompileShader(vertex);
        CheckErrors(vertex, Type::Vertex);

        const char* fragmentStr = fragmentCode.c_str();
        const uint32_t fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fragmentStr, nullptr);
        glCompileShader(fragment);
        CheckErrors(fragment, Type::Fragment);

        id_ = glCreateProgram();
        glAttachShader(id_, vertex);
        glAttachShader(id_, fragment);

        glLinkProgram(id_);
        CheckErrors(id_, Type::Program);

        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }

    void OpenGLShader::CheckErrors(uint32_t shader, Type type)
    {
        int success;
        char infoLog[512];
        if (type != Type::Program)
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 512, nullptr, infoLog);
                CORE_ERROR("Error Compiling Shader: {0}", infoLog);
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, 512, nullptr, infoLog);
                CORE_ERROR("Error Linking Program: {0}", infoLog);
            }
        }

        
    }

    std::string OpenGLShader::FileToString(const std::string& GLSLFilePath)
    {
        std::ifstream in(GLSLFilePath, std::ios::in, std::ios::binary);
        std::string result;

        if (in)
        {
            in.seekg(0, std::ios::end);
            result.resize(in.tellg());
            in.seekg(0, std::ios::beg);
            in.read(&result[0], result.size());
            in.close();
        }
        else CORE_ERROR("Error in load GLSL File: {0}", GLSLFilePath);
        
        return result;
    }

    void OpenGLShader::Uniform(const char* name, int value) const
    {
        glUniform1i(glGetUniformLocation(id_, name), value);
    }

    void OpenGLShader::Uniform(const char* name, bool value) const
    {
        glUniform1i(glGetUniformLocation(id_, name), static_cast<int>(value));
    }

    void OpenGLShader::Uniform(const char* name, float value) const
    {
        glUniform1f(glGetUniformLocation(id_, name), value);
    }

    void OpenGLShader::Uniform(const char* name, float value1, float value2) const
    {
        glUniform2f(glGetUniformLocation(id_, name), value1, value2);
    }

    void OpenGLShader::Uniform(const char* name, float value1, float value2, float value3) const
    {
        glUniform3f(glGetUniformLocation(id_, name), value1, value2, value3);
    }

    void OpenGLShader::Uniform(const char* name, float value1, float value2, float value3, float value4) const
    {
        glUniform4f(glGetUniformLocation(id_, name), value1, value2, value3, value4);
    }

    void OpenGLShader::Uniform(const char* name, const glm::vec2& value) const
    {
        glUniform2fv(glGetUniformLocation(id_, name), 1, glm::value_ptr(value));
    }

    void OpenGLShader::Uniform(const char* name, const glm::vec3& value) const
    {
        glUniform3fv(glGetUniformLocation(id_, name), 1, glm::value_ptr(value));
    }

    void OpenGLShader::Uniform(const char* name, const glm::vec4& value) const
    {
        glUniform4fv(glGetUniformLocation(id_, name), 1, glm::value_ptr(value));
    }

    void OpenGLShader::Uniform(const char* name, const glm::mat2& value) const
    {
        glUniformMatrix2fv(glGetUniformLocation(id_, name), 1, GL_FALSE, glm::value_ptr(value));
    }

    void OpenGLShader::Uniform(const char* name, const glm::mat3& value) const
    {
        glUniformMatrix3fv(glGetUniformLocation(id_, name), 1, GL_FALSE, glm::value_ptr(value));
    }

    void OpenGLShader::Uniform(const char* name, const glm::mat4& value) const
    {
        glUniformMatrix4fv(glGetUniformLocation(id_, name), 1, GL_FALSE, glm::value_ptr(value));
    }
}
