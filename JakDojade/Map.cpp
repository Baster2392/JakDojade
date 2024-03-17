#include "Map.h"

Map::Map(int width, int height)
{
	this->width = width;
	this->height = height;
	this->charMap = new char* [width];
	this->intMap = new int* [width];

	for (int i = 0; i < width; i++)
	{
		this->charMap[i] = new char[height];
		this->intMap[i] = new int[height];

		for (int j = 0; j < height; j++)
		{
			this->intMap[i][j] = 0;
		}
	}
}

Map::~Map()
{
	for (int i = 0; i < this->cities.getSize(); i++)
	{
		delete this->cities[i];
	}
}

void Map::loadFromFile()
{
	int rows, lines;
	FILE* file;
	fopen_s(&file, "map.txt", "r");
	fscanf_s(file, "%d %d", &rows, &lines);
	char line[10000];

	fgets(line, 10000, file);
	//std::cout << line;
	for (int i = 0; i < lines; i++)
	{
		fgets(line, 10000, file);
		//std::cout << line;
		for (int j = 0; j < rows; j++)
		{
			if (line[j] == '*')
			{
				this->cityPointsX.pushBack(j);
				this->cityPointsY.pushBack(i);
			}

			this->charMap[j][i] = line[j];
		}
	}

	int positionX, positionY;
	City* newCity;
	for (int i = 0; i < this->cityPointsX.getSize(); i++)
	{
		positionX = this->cityPointsX[i];
		positionY = this->cityPointsY[i];
		newCity = new City(findCityName(positionX, positionY), positionX, positionY, this->cities.getSize());
		this->cities.pushBack(newCity);
		this->map.add(newCity);
	}

	// loading airlines
	int numberOfAirlines, distanceAir;
	char start[100], target[100];
	City* startCity, * targetCity;
	fscanf_s(file, "%d", &numberOfAirlines);

	for (int i = 0; i < numberOfAirlines; i++)
	{
		fscanf_s(file, "%s %s %d", start, 100, target, 100, &distanceAir);
		startCity = getCityByName(start);
		targetCity = getCityByName(target);

		startCity->addNeighbor(targetCity, distanceAir);
	}

	int numberOfQueries = 0, mode = 0;
	fscanf_s(file, "%d", &numberOfQueries);
	String str1, str2;

	checkRoads();

	for (int i = 0; i < numberOfQueries; i++)
	{
		fscanf_s(file, "%s %s %d", start, 100, target, 100, &mode);
		str1 = start;
		str2 = target;
		findShortestPath(str1, str2, mode);
	}

	fclose(file);
}

void Map::loadMap()
{
	// loading map
	char c;
	for (int i = 0; i < this->height; i++)
	{
		for (int j = 0; j < this->width; j++)
		{
			c = getchar();

			if (c == '*')
			{
				this->cityPointsX.pushBack(j);
				this->cityPointsY.pushBack(i);
			}

			this->charMap[j][i] = c;
		}

		getchar();
	}

	int positionX, positionY;
	City* newCity;
	for (int i = 0; i < this->cityPointsX.getSize(); i++)
	{
		positionX = this->cityPointsX[i];
		positionY = this->cityPointsY[i];
		newCity = new City(findCityName(positionX, positionY), positionX, positionY, this->cities.getSize());
		this->cities.pushBack(newCity);
		this->map.add(newCity);
	}

	// loading airlines
	int numberOfAirlines, distanceAir;
	char start[100], target[100];
	City* startCity, * targetCity;
	scanf_s("%d", &numberOfAirlines);

	for (int i = 0; i < numberOfAirlines; i++)
	{
		scanf_s("%s %s %d", start, 100, target, 100, &distanceAir);
		startCity = getCityByName(start);
		targetCity = getCityByName(target);

		startCity->addNeighbor(targetCity, distanceAir);
	}

	int numberOfQueries = 0, mode = 0;
	scanf_s("%d", &numberOfQueries);
	String str1, str2;

	checkRoads();

	for (int i = 0; i < numberOfQueries; i++)
	{
		scanf_s("%s %s %d", start, 100, target, 100, &mode);
		str1 = start;
		str2 = target;
		findShortestPath(str1, str2, mode);
	}
}

String Map::findCityName(int positionX, int positionY)
{
	String name = "";
	int pointerPosX = positionX, pointerPosY = positionY;

	// name of city on right
	if (positionX < this->width - 1 &&
		this->charMap[positionX + 1][positionY] != '*' &&
		this->charMap[positionX + 1][positionY] != '.' &&
		this->charMap[positionX + 1][positionY] != '#')
	{
		pointerPosX++;
		while (pointerPosX < this->width &&
			this->charMap[pointerPosX][pointerPosY] != '*' &&
			this->charMap[pointerPosX][pointerPosY] != '.' &&
			this->charMap[pointerPosX][pointerPosY] != '#')
		{
			name.append(this->charMap[pointerPosX][pointerPosY]);
			pointerPosX++;
		}
	}
	// name of city on left
	else
		if (positionX > 0 &&
			this->charMap[positionX - 1][positionY] != '*' &&
			this->charMap[positionX - 1][positionY] != '.' &&
			this->charMap[positionX - 1][positionY] != '#')
		{
			pointerPosX--;
			while (pointerPosX >= 0 &&
				this->charMap[pointerPosX][pointerPosY] != '*' &&
				this->charMap[pointerPosX][pointerPosY] != '.' &&
				this->charMap[pointerPosX][pointerPosY] != '#')
			{
				pointerPosX--;
			}

			pointerPosX++;
			while (this->charMap[pointerPosX][pointerPosY] != '*')
			{
				name.append(this->charMap[pointerPosX][pointerPosY]);
				pointerPosX++;
			}
		}
	// name of city above
	else
		if (positionY > 0 &&
			this->charMap[positionX][positionY - 1] != '*' &&
			this->charMap[positionX][positionY - 1] != '.' &&
			this->charMap[positionX][positionY - 1] != '#')
		{
		pointerPosY--;
			while (pointerPosX >= 0 &&
				this->charMap[pointerPosX][pointerPosY] != '*' &&
				this->charMap[pointerPosX][pointerPosY] != '.' &&
				this->charMap[pointerPosX][pointerPosY] != '#')
			{
				pointerPosX--;
			}

			pointerPosX++;
			while (pointerPosX < this->width &&
				this->charMap[pointerPosX][pointerPosY] != '*' &&
				this->charMap[pointerPosX][pointerPosY] != '.' &&
				this->charMap[pointerPosX][pointerPosY] != '#')
			{
				name.append(this->charMap[pointerPosX][pointerPosY]);
				pointerPosX++;
			}
		}
	// name of city below
	else
		if (positionY < this->height - 1 &&
			this->charMap[positionX][positionY + 1] != '*' &&
			this->charMap[positionX][positionY + 1] != '.' &&
			this->charMap[positionX][positionY + 1] != '#')
		{
			pointerPosY++;
			while (pointerPosX >= 0 &&
				this->charMap[pointerPosX][pointerPosY] != '*' &&
				this->charMap[pointerPosX][pointerPosY] != '.' &&
				this->charMap[pointerPosX][pointerPosY] != '#')
			{
				pointerPosX--;
			}

			pointerPosX++;

			while (pointerPosX < this->width &&
				this->charMap[pointerPosX][pointerPosY] != '*' &&
				this->charMap[pointerPosX][pointerPosY] != '.' &&
				this->charMap[pointerPosX][pointerPosY] != '#')
			{
				name.append(this->charMap[pointerPosX][pointerPosY]);
				pointerPosX++;
			}
		}
	// name of city in top right corner
	else
		if (positionY > 0 &&
			positionX < this->width - 1 &&
			this->charMap[positionX + 1][positionY - 1] != '*' &&
			this->charMap[positionX + 1][positionY - 1] != '.' &&
			this->charMap[positionX + 1][positionY - 1] != '#')
		{
			pointerPosX++;
			pointerPosY--;
			while (pointerPosX >= 0 &&
				this->charMap[pointerPosX][pointerPosY] != '*' &&
				this->charMap[pointerPosX][pointerPosY] != '.' &&
				this->charMap[pointerPosX][pointerPosY] != '#')
			{
				pointerPosX--;
			}

			pointerPosX++;
			while (pointerPosX < this->width &&
				this->charMap[pointerPosX][pointerPosY] != '*' &&
				this->charMap[pointerPosX][pointerPosY] != '.' &&
				this->charMap[pointerPosX][pointerPosY] != '#')
			{
				name.append(this->charMap[pointerPosX][pointerPosY]);
				pointerPosX++;
			}
		}
	// name of city in bottom right corner
	else
		if (positionY < this->height - 1 &&
			positionX < this->width - 1 &&
			this->charMap[positionX + 1][positionY + 1] != '*' &&
			this->charMap[positionX + 1][positionY + 1] != '.' &&
			this->charMap[positionX + 1][positionY + 1] != '#')
		{
			pointerPosX++;
			pointerPosY++;
			while (pointerPosX >= 0 &&
				this->charMap[pointerPosX][pointerPosY] != '*' &&
				this->charMap[pointerPosX][pointerPosY] != '.' &&
				this->charMap[pointerPosX][pointerPosY] != '#')
			{
				pointerPosX--;
			}

			pointerPosX++;
			while (pointerPosX < this->width &&
				this->charMap[pointerPosX][pointerPosY] != '*' &&
				this->charMap[pointerPosX][pointerPosY] != '.' &&
				this->charMap[pointerPosX][pointerPosY] != '#')
			{
				name.append(this->charMap[pointerPosX][pointerPosY]);
				pointerPosX++;
			}
		}
	// name of city in top left corner
	else
		if (positionY > 0 &&
			positionX > 0 &&
			this->charMap[positionX - 1][positionY - 1] != '*' &&
			this->charMap[positionX - 1][positionY - 1] != '.' &&
			this->charMap[positionX - 1][positionY - 1] != '#')
		{
			pointerPosX--;
			pointerPosY--;
			while (pointerPosX >= 0 &&
				this->charMap[pointerPosX][pointerPosY] != '*' &&
				this->charMap[pointerPosX][pointerPosY] != '.' &&
				this->charMap[pointerPosX][pointerPosY] != '#')
			{
				pointerPosX--;
			}

			pointerPosX++;
			while (pointerPosX < this->width &&
				this->charMap[pointerPosX][pointerPosY] != '*' &&
				this->charMap[pointerPosX][pointerPosY] != '.' &&
				this->charMap[pointerPosX][pointerPosY] != '#')
			{
				name.append(this->charMap[pointerPosX][pointerPosY]);
				pointerPosX++;
			}
							}
	// name of city in bottom left corner
	else
		if (positionY < this->height - 1 &&
			positionX > 0 &&
			this->charMap[positionX - 1][positionY + 1] != '*' &&
			this->charMap[positionX - 1][positionY + 1] != '.' &&
			this->charMap[positionX - 1][positionY + 1] != '#')
		{
			pointerPosX--;
			pointerPosY++;
			while (pointerPosX >= 0 &&
				this->charMap[pointerPosX][pointerPosY] != '*' &&
				this->charMap[pointerPosX][pointerPosY] != '.' &&
				this->charMap[pointerPosX][pointerPosY] != '#')
			{
				pointerPosX--;
			}

			pointerPosX++;
			while (pointerPosX < this->width &&
				this->charMap[pointerPosX][pointerPosY] != '*' &&
				this->charMap[pointerPosX][pointerPosY] != '.' &&
				this->charMap[pointerPosX][pointerPosY] != '#')
			{
				name.append(this->charMap[pointerPosX][pointerPosY]);
				pointerPosX++;
			}
		}

	return name;
}

City* Map::getCityAtPosition(int positionX, int positionY)
{
	for (int i = 0; i < this->cities.getSize(); i++)
	{
		if (this->cities[i]->getPositionX() == positionX && this->cities[i]->getPositionY() == positionY)
		{
			return this->cities[i];
		}
	}

	return nullptr;
}

City* Map::getCityByName(String& name)
{
	return map.get(name);
}

City* Map::getCityByName(char* name)
{
	String strName(name);
	return map.get(strName);
}

City* Map::getCityByNameAndId(String& name, int id)
{
	return map.get(name, id);
}

int Map::getIndexOfCity(String& name)
{
	for (int i = 0; i < this->cities.getSize(); i++)
	{
		if (this->cities[i]->getName().equal(name.c_str()))
		{
			return i;
		}
	}

	std::cout << "Not found" << std::endl;
	return -1;
}

void Map::checkRoads()
{
	City* currentCity, * foundCity;
	Vector<int> pointsX;
	Vector<int> pointsY;
	Vector<int> visitedX;
	Vector<int> visitedY;
	int posX, posY;
	int currentX, currentY;

	for (int i = 0; i < this->cities.getSize(); i++)
	{
		currentCity = this->cities[i];
		pointsX.pushBack(currentCity->getPositionX());
		pointsY.pushBack(currentCity->getPositionY());

		while (pointsX.getSize() > 0)
		{
			currentX = pointsX[0];
			currentY = pointsY[0];
			pointsX.erase(0);
			pointsY.erase(0);

			// found city
			if (currentX > 0 && this->intMap[currentX - 1][currentY] == 0 && this->charMap[currentX - 1][currentY] == '*'
				&& (currentX - 1 != currentCity->getPositionX() || currentY != currentCity->getPositionY()))
			{
				foundCity = getCityAtPosition(currentX - 1, currentY);
				currentCity->addNeighbor(foundCity, this->intMap[currentX][currentY] + 1);
			}

			if (currentX < this->width - 1 && this->intMap[currentX + 1][currentY] == 0 && this->charMap[currentX + 1][currentY] == '*'
				&& (currentX + 1 != currentCity->getPositionX() || currentY != currentCity->getPositionY()))
			{
				foundCity = getCityAtPosition(currentX + 1, currentY);
				currentCity->addNeighbor(foundCity, this->intMap[currentX][currentY] + 1);
			}

			if (currentY > 0 && this->intMap[currentX][currentY - 1] == 0 && this->charMap[currentX][currentY - 1] == '*'
				&& (currentX != currentCity->getPositionX() || currentY - 1 != currentCity->getPositionY()))
			{
				foundCity = getCityAtPosition(currentX, currentY - 1);
				currentCity->addNeighbor(foundCity, this->intMap[currentX][currentY] + 1);
			}

			if (currentY < this->height - 1 && this->intMap[currentX][currentY + 1] == 0 && this->charMap[currentX][currentY + 1] == '*'
				&& (currentX != currentCity->getPositionX() || currentY + 1 != currentCity->getPositionY()))
			{
				foundCity = getCityAtPosition(currentX, currentY + 1);
				currentCity->addNeighbor(foundCity, this->intMap[currentX][currentY] + 1);
			}

			// found road
			if (currentX > 0 && this->intMap[currentX - 1][currentY] == 0 && this->charMap[currentX - 1][currentY] == '#')
			{
				this->intMap[currentX - 1][currentY] = this->intMap[currentX][currentY] + 1;
				pointsX.pushBack(currentX - 1);
				pointsY.pushBack(currentY);
				visitedX.pushBack(currentX - 1);
				visitedY.pushBack(currentY);
			}

			if (currentX < this->width - 1 && this->intMap[currentX + 1][currentY] == 0 && this->charMap[currentX + 1][currentY] == '#')
			{
				this->intMap[currentX + 1][currentY] = this->intMap[currentX][currentY] + 1;
				pointsX.pushBack(currentX + 1);
				pointsY.pushBack(currentY);
				visitedX.pushBack(currentX + 1);
				visitedY.pushBack(currentY);
			}

			if (currentY > 0 && this->intMap[currentX][currentY - 1] == 0 && this->charMap[currentX][currentY - 1] == '#')
			{
				this->intMap[currentX][currentY - 1] = this->intMap[currentX][currentY] + 1;
				pointsX.pushBack(currentX);
				pointsY.pushBack(currentY - 1);
				visitedX.pushBack(currentX);
				visitedY.pushBack(currentY - 1);
			}

			if (currentY < this->height - 1 && this->intMap[currentX][currentY + 1] == 0 && this->charMap[currentX][currentY + 1] == '#')
			{
				this->intMap[currentX][currentY + 1] = this->intMap[currentX][currentY] + 1;
				pointsX.pushBack(currentX);
				pointsY.pushBack(currentY + 1);
				visitedX.pushBack(currentX);
				visitedY.pushBack(currentY + 1);
			}
		}

		zeroIntMap(&visitedX, &visitedY);
		visitedX.clear();
		visitedY.clear();
	}
}

void Map::printMap()
{
	std::cout << std::endl;
	for (int i = 0; i < this->height; i++)
	{
		for (int j = 0; j < this->width; j++)
		{
			std::cout << this->intMap[j][i] << " ";
		}

		std::cout << std::endl;
	}

	std::cout << std::endl;

	for (int i = 0; i < this->cityPointsX.getSize(); i++)
	{
		std::cout << this->cityPointsX[i] << " " << this->cityPointsY[i] << std::endl;
	}
}

void Map::printCities()
{
	for (int i = 0; i < this->cities.getSize(); i++)
	{
		std::cout << this->cities[i]->getName().c_str() << " " << this->cities[i]->getPositionX() << " " << this->cities[i]->getPositionY() << std::endl;
		this->cities[i]->printNeighbors();
	}
}

void Map::findShortestPath(String& start, String& target, int mode)
{
	if (start.equal(target.c_str()))
	{
		std::cout << 0 << std::endl;
		return;
	}

	int* distances = new int[this->cities.getSize()];
	City** listOfPrev = new City*[this->cities.getSize()];

	City* startCity = getCityByName(start);
	City* targetCity = getCityByName(target);
	Vector<City*> previous;
	PriorityQueue priorQueue;

	for (int i = 0; i < this->cities.getSize(); i++)
	{
		distances[i] = INFINITY;
		listOfPrev[i] = nullptr;
	}

	// create first node with distance 0
	ListOfNeighbors currentNode = ListOfNeighbors();
	currentNode.city = startCity;
	currentNode.distance = 0;
	currentNode.nextNode = nullptr;

	priorQueue.push(currentNode);

	while (priorQueue.size() != 0)
	{
		// get verticle and pop
		currentNode = priorQueue.top();
		priorQueue.pop();

		// check if verticle is visited
		for (int i = 0; i < previous.getSize(); i++)
		{
			if (previous[i]->getIndex() == currentNode.city->getIndex())
			{
				continue;
			}
		}

		// mark as visited
		previous.pushBack(currentNode.city);

		// for every neighbor of currentnode
		ListOfNeighbors* curNeigh = currentNode.city->listOfNeighbors;
		while (curNeigh != nullptr)
		{
			// calculate new distance
			int index = curNeigh->city->getIndex();
			int newDistance = currentNode.distance + curNeigh->distance;
			if (newDistance < distances[index])
			{
				distances[index] = newDistance;
				listOfPrev[index] = currentNode.city;

				ListOfNeighbors newNeigh = ListOfNeighbors();
				newNeigh.city = curNeigh->city;
				newNeigh.distance = newDistance;
				newNeigh.nextNode = nullptr;
				priorQueue.push(newNeigh);
			}

			curNeigh = curNeigh->nextNode;
		}
	}

	std::cout << distances[targetCity->getIndex()];

	if (mode == PRINT_PATH_MODE)
	{
		// creating shortest path
		Vector<City*> shortestPath;
		City* currentCity = targetCity;

		while (currentCity != startCity && currentCity != nullptr)
		{
			shortestPath.pushBack(currentCity);
			currentCity = listOfPrev[currentCity->getIndex()];
		}

		for (int i = shortestPath.getSize() - 1; i > 0; i--)
		{
			std::cout << " " << shortestPath[i]->getName().c_str();
		}
	}

	std::cout << std::endl;

	delete[] listOfPrev;
	delete[] distances;
}

void Map::zeroIntMap(Vector<int>* pointsX, Vector<int>* pointsY)
{
	for (int i = 0; i < pointsX->getSize(); i++)
	{
		this->intMap[(*pointsX)[i]][(*pointsY)[i]] = 0;
	}
}

int Map::min(int num1, int num2)
{
	if (num1 < num2)
	{
		return num1;
	}

	return num2;
}
