#pragma once
#include "String.h"
#include "Vector.h"

template <typename T>
class Dictionary
{
private:
	struct Node
	{
		String key;
		T value;
		Node* next;
	};

	Vector<Node*> tab;
};