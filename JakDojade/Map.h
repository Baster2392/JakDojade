#pragma once
#include "Vector.h"
#include "String.h"
#include "City.h"
#include <iostream>

class Map
{
private:
	Vector<int> cityPointsX;
	Vector<int> cityPointsY;
	Vector<City*> cities;

	int width;
	int height;
	char** charMap;
	int** intMap;
public:

	Map(int width, int height);
	~Map();

	void loadMap();
	void findCitys();
	String getCityName(int positionX, int positionY);
	City* getCityAtPosition(int positionX, int positionY);
	City* getCityByName(String& name);
	void checkRoads();
	void printMap();
	void printCities();

	void zeroIntMap();
};