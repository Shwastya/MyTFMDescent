#pragma once

#include "../src/engine/mhpch.cpp"
	

namespace MHelmet
{
	struct Node
	{
		Node() {};

		virtual ~Node() = default;

		virtual void Join() = 0;
		virtual void Free() = 0;


		virtual void Update(DeltaTime dt) = 0;
	};
}
