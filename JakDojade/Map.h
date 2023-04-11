#pragma once
#include "Vector.h"
#include "String.h"
#include <iostream>

class Map
{
private:
	Vector<int> cityPointsX;
	Vector<int> cityPointsY;

	int width;
	int height;
	char** charMap;
	int** intMap;
public:

	Map(int width, int height);

	void loadMap();
	void findCitys();
	String getCityName(int positionX, int positionY);
	void checkRoads();
	void printMap();

	void zeroIntMap();
};