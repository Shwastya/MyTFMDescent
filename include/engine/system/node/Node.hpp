#pragma once

#include <MHpch.h>

namespace MHelmet
{
	struct Node
	{
		Node() {};

		virtual ~Node() = default;

		virtual void Join() = 0;
		virtual void Free() = 0;


		virtual void Update(TimeStep dt) = 0;
	};
}
