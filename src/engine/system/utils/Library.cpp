#include "engine/system/utils/Library.hpp"
#include <MHpch.h>
#include "engine/system/MHCore.hpp"

namespace MHelmet
{
	void ShaderLib::Add(const std::string& name, const RefCount<Shader>& newShader)
	{
		if (CheckNameInLibrary(name, Check::Pull))
		{
			TRACE("Added '{0}' to Shader Library", name);
			m_ShadersLib[name] = newShader;
		}		
	}

	RefCount<Shader> ShaderLib::Get(const std::string& name)
	{
		if (CheckNameInLibrary(name, Check::Take))
		{
			return m_ShadersLib[name];
		}		
	}

	RefCount<Shader> ShaderLib::Load(const std::string& name, const std::string& filePath)
	{
		RefCount<Shader> shader = Shader::Create(name, filePath);
		Add(name, shader);
		return shader;
	}

	bool ShaderLib::CheckNameInLibrary(const std::string& name, Check mode) const
	{
		if (mode == ShaderLib::Check::Pull)
		{
			if (!(m_ShadersLib.find(name) == m_ShadersLib.end()))
			{
				ERROR("That name already exists");
				return false;
			}
		}
		else
		{
			if (!(m_ShadersLib.find(name) != m_ShadersLib.end()))
			{
				ERROR("Not in library");
				return false;
			}
		}
		return true;		
	}
}