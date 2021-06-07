#pragma once

struct Node
{
	Node() {};

	virtual ~Node() = default;

	virtual void Join() = 0;
	virtual void Free() = 0;


	virtual void Update() = 0;
};