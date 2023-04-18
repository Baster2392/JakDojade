#pragma once
#include "Vector.h"
#include "String.h"
#include "City.h"
#include "PriorityQueue.h"
#include <iostream>
#include <limits.h>
#include <fstream>

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

	void loadFromFile();

	void loadMap();
	String getCityName(int positionX, int positionY);
	City* getCityAtPosition(int positionX, int positionY);
	City* getCityByName(String& name);
	City* getCityByName(char* name);
	int getIndexOfCity(String& name);
	void checkRoads();
	void printMap();
	void printCities();
	void findShortestPath(String& start, String& target);

	void zeroIntMap();

	static int min(int num1, int num2);
};