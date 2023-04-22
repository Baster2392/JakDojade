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
	int index;

public:
	ListOfNeighbors* listOfNeighbors;

	City();
	City(String& name, int positionX, int positionY, int index);
	City(String&& name, int positionX, int positionY, int index);
	~City();

	String& getName();
	int getPositionX();
	int getPositionY();
	int getNumberOfNeighbors();
	void setIndex(int index);
	int getIndex();

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

