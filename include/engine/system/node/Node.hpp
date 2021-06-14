#pragma once
#include "engine/system/MHCore.hpp"

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
