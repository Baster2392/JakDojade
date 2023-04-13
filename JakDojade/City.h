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
	int positionX;
	int positionY;

public:
	City(String& name, int positionX, int positionY);
	City(String&& name, int positionX, int positionY);

	String& getName();
	int getPositionX();
	int getPositionY();

	void addNeighbor(String& name, int distance);
	void printNeighbors();
};

