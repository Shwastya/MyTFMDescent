#pragma once
#include "engine/system/renderer/shader.hpp"
#include <unordered_map>


namespace MHelmet
{
    struct ShaderLib
    {
        enum class Check
        {
            Pull, Take
        };

        void Add(const std::string& name, const RefCount<Shader>& newShader);

        RefCount<Shader> Get(const std::string& name);
        RefCount<Shader> Load(const std::string& name, const std::string& filePath);
        
        bool CheckNameInLibrary(const std::string& name, Check mode) const;

    private:

        std::unordered_map<std::string, RefCount<Shader>> m_ShadersLib;
    };
}
