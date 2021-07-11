#include "engine/system/scene/SerializerScene.hpp"
#include "engine/system/scene/Entity.hpp"
#include "engine/system/scene/Components.hpp"
#include <fstream>
#include "yaml-cpp/yaml.h"







namespace MHelmet
{
	SerializerScene::SerializerScene(const RefCount<Scene>& scene)
		:m_Scene(scene)
	{
	}

	static void SerializeEntity(YAML::Emitter& out, Entity entity)
	{
		out << YAML::BeginMap;
		out << YAML::Key << "Entity" << YAML::Value << "124234123424320";		

		if (entity.HasComponent<TagComponent>())
		{
			out << YAML::Key << "TagComponent";
			out << YAML::BeginMap;

			auto& tag = entity.GetComponent<TagComponent>().Tag;
			out << YAML::Key << "Tag" << YAML::Value << tag;

			out << YAML::EndMap;
		}

		out << YAML::EndMap;
	}

	void SerializerScene::Serialize(const std::string& filePath)
	{
		YAML::Emitter out;
		out << YAML::BeginMap;
		out << YAML::Key << "Scene" << YAML::Value << "Unntitled";
		out << YAML::Key << "Entities" << YAML::Value << YAML::BeginSeq;

		m_Scene->m_Registry.each([&](auto entityID) 
		{
				Entity entity = { entityID, m_Scene.get() };
				if (!entity)
					return;
				SerializeEntity(out, entity);
		});
		out << YAML::EndSeq;
		out << YAML::EndMap;

		std::ofstream fout(filePath);
		fout << out.c_str();
	}
	void SerializerScene::SerializeRuntime(const std::string& filePath)
	{
		// not
	}
	bool SerializerScene::Deserialize(const std::string& filePath)
	{
		return false;
	}
	bool SerializerScene::DeserializeRuntime(const std::string& filepath)
	{
		return false;
	}
}