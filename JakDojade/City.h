#pragma once
#include <iostream>
#include "String.h"

struct ListOfNeighbors;

class City
{
private:
	String name;
	int positionX;
	int positionY;
	int numberOfNeighbors;

public:
	ListOfNeighbors* listOfNeighbors;

	City(String& name, int positionX, int positionY);
	City(String&& name, int positionX, int positionY);
	~City();

	String& getName();
	int getPositionX();
	int getPositionY();
	int getNumberOfNeighbors();

	void addNeighbor(City* city, int distance);
	ListOfNeighbors* getSmallestVertex();
	void printNeighbors();
};

struct ListOfNeighbors
{
	City* city;
	int distance;
	ListOfNeighbors* nextNode;
};

