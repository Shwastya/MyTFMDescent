#include "engine/system/MHCore.hpp"
#include "engine/system/platform/RenderAPI/OpenGL/OpenGLShader.hpp"
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <sstream>

namespace MHelmet
{
    static GLenum FormatType(const Type& type)
    {        
        switch (type)
        {
            case Type::Vertex:   return GL_VERTEX_SHADER;
            case Type::Fragment: return GL_FRAGMENT_SHADER;
            case Type::Geometry: return GL_GEOMETRY_SHADER; 
            case Type::Program:  
            {
                CORE_ERROR("Not Shader");
                break;
            }
            default: CORE_ERROR("Unknown shader Format!");
        }

        return 0;
    }

    OpenGLShader::OpenGLShader(const std::string& vertexPath, const std::string& fragmentPath)
    {
        std::string vertexCode   = LoadShaderFromString(vertexPath);
        std::string fragmentCode = LoadShaderFromString(vertexPath);

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

        std::string ShaderSrc = LoadShaderFromString(GLSLFile);
        SplitGlslSource(ShaderSrc);        
    }

    ShaderTypesMap OpenGLShader::SplitGlslSource(const std::string& GLSLSource)
    {
        std::string vertexCode, fragmentCode;  



        const char* token = "#TYPE";
        size_t tokenLenght = strlen(token);
        size_t pos = GLSLSource.find(token, 0);

        while (pos != std::string::npos)
        {
            size_t eol = GLSLSource.find_first_of("\r\n", pos);

            size_t begin = pos + tokenLenght + 1;
            std::string type = GLSLSource.substr(begin, eol - begin);

            size_t nextLinePos = GLSLSource.find_first_not_of("\r\n", eol);
            pos = GLSLSource.find(token, nextLinePos);

            if (type == "VERTEX")
                vertexCode = GLSLSource.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? GLSLSource.size() - 1 : nextLinePos));

            if (type == "FRAGMENT")
                fragmentCode = GLSLSource.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? GLSLSource.size() - 1 : nextLinePos));
        }
        CompileShader(vertexCode, fragmentCode);

        return ShaderTypesMap();
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


    std::string OpenGLShader::LoadShaderFromString(const std::string& GLSLFilePath)
    {
        std::ifstream in(GLSLFilePath, std::ios::in, std::ios::binary);
        std::string source;

        if (in)
        {
            in.seekg(0, std::ios::end);
            source.resize(in.tellg());
            in.seekg(0, std::ios::beg);
            in.read(&source[0], source.size());
            in.close();
        }
        else CORE_ERROR("Error in load GLSL File: {0}", GLSLFilePath);

        return source;
    }

    void OpenGLShader::LoadShaderFromChar(const char* path, std::string* code)
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

   
    

    void OpenGLShader::Compile(const ShaderTypesMap& ShaderSrc)
    {

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
