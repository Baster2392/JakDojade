#pragma once
#include <iostream>
#include "String.h"
class City
{
private:
	struct ListOfNeighbors
	{
		String name;
		int distance;
		ListOfNeighbors* nextNode;
	};

	String name;
	ListOfNeighbors* listOfNeighbors;

public:
	City(String& name);
	City(String&& name);

	String& getName();
	void addNeighbor(String& name, int distance);
	void printNeighbors();
};

