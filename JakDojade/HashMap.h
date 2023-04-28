#pragma once
#include "String.h"
#include "City.h"
#define SIZE 10007

struct Node
{
	City* city;
	Node* nextNode;
};

class HashMap
{
private:
	Node* tab[SIZE];

public:
	HashMap()
	{
		for (int i = 0; i < SIZE; i++)
		{
			tab[i] = nullptr;
		}
	}

	~HashMap()
	{
		Node* currentNode, *toDelete;
		for (int i = 0; i < SIZE; i++)
		{
			currentNode = tab[i];
			while (currentNode != nullptr)
			{
				toDelete = currentNode;
				currentNode = currentNode->nextNode;
				delete toDelete;
			}
		}
	}

	int hash(String& key)
	{
		int index = 0;
		for (int i = 0; i < key.size(); i++)
		{
			index += (int)key[i] * (i + 1);
		}

		return index % SIZE;
	}

	void addToChain(int index, City* value)
	{
		Node* newNode = new Node;
		newNode->city = value;
		newNode->nextNode = nullptr;

		Node* currentNode = this->tab[index];

		if (currentNode == nullptr)
		{
			this->tab[index] = newNode;
			return;
		}

		while (currentNode->nextNode != nullptr)
		{
			currentNode = currentNode->nextNode;
		}

		currentNode->nextNode = newNode;
	}

	void add(City* value)
	{
		int index = hash(value->getName());
		addToChain(index, value);
	}

	City* get(String& key)
	{
		int index = hash(key);
		Node* currentNode = this->tab[index];

		while (currentNode != nullptr)
		{
			if (currentNode->city->getName().equal(key.c_str()))
			{
				return currentNode->city;
			}

			currentNode = currentNode->nextNode;
		}

		return nullptr;
	}

	City* get(String& key, int id)
	{
		int index = hash(key);
		Node* currentNode = this->tab[index];

		while (currentNode != nullptr)
		{
			if (currentNode->city->getIndex() == id)
			{
				return currentNode->city;
			}

			currentNode = currentNode->nextNode;
		}

		return nullptr;
	}
};
