#pragma once

/*
* Cuando inicialicemos el sistema 
* le pasaremos una referencia al manager de entidades
* eso permitira que el sistema llame al manager 
* pidiendo ciertas entidades
*/

#include "engine/texture.hpp"

#include "engine/geometry/cube.hpp"

#include "vector";

namespace TFM_ECS {


	struct Entity_t // gross entity attempt
	{
		explicit Entity_t(float arista, const char* path)
		: _arista { arista }, _path { path }
		{
			cube.reserve(48);
		}

      

		float _arista { 1.0f };
		const char* _path;

		Texture tex { _path, Texture::Format::RGB };
		std::vector<Cube> cube { 1.0f };
	};
	


	struct EntityManager_t 
	{
		explicit EntityManager_t();

		std::vector<Entity_t> cube ;
	};
	




} // namespace TFM_ECS