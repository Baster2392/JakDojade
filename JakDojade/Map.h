#pragma once
#include "Vector.h"
#include "String.h"
#include "City.h"
#include "PriorityQueue.h"
#include "HashMap.h"
#include <iostream>
#include <limits.h>
#include <fstream>

#define PRINT_PATH_MODE 1
#define ONLY_DISTANCE_MODE 0
#define INFINITY 10000000

class Map
{
private:
	Vector<int> cityPointsX;
	Vector<int> cityPointsY;
	Vector<City*> cities;
	HashMap map;

	int width;
	int height;
	char** charMap;
	int** intMap;
public:

	Map(int width, int height);
	~Map();

	void loadFromFile();

	void loadMap();
	String findCityName(int positionX, int positionY);
	City* getCityAtPosition(int positionX, int positionY);
	City* getCityByName(String& name);
	City* getCityByName(char* name);
	City* getCityByNameAndId(String& name, int id);
	int getIndexOfCity(String& name);
	void checkRoads();
	void printMap();
	void printCities();
	void findShortestPath(String& start, String& target, int mode);

	void zeroIntMap(Vector<int>* pointsX, Vector<int>* pointsY);

	static int min(int num1, int num2);
};