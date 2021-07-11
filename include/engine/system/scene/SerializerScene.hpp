#pragma once
#include "Scene.hpp"

namespace MHelmet
{
	class SerializerScene
	{
	public:
		SerializerScene(const RefCount<Scene>& scene);

		void Serialize(const std::string& filePath);
		void SerializeRuntime(const std::string& filePath);
		bool Deserialize(const std::string& filePath);
		bool DeserializeRuntime(const std::string& filepath);


	private:
		RefCount<Scene> m_Scene;
	};

}