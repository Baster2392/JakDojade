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
	char line[1000];

	fgets(line, 100, file);
	for (int i = 0; i < lines; i++)
	{
		fgets(line, 100, file);
		std::cout << line;
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
	for (int i = 0; i < this->cityPointsX.getSize(); i++)
	{
		positionX = this->cityPointsX[i];
		positionY = this->cityPointsY[i];
		this->cities.pushBack(new City(getCityName(positionX, positionY), positionX, positionY));
	}

	// loading airlines
	int numberOfAirlines, distanceAir;
	char start[100], target[100];
	City* startCity, * targetCity;
	fscanf_s(file, "%d", &numberOfAirlines);
	//std::cout << numberOfAirlines << std::endl;

	for (int i = 0; i < numberOfAirlines; i++)
	{
		fscanf_s(file, "%s %s %d", start, 100, target, 100, &distanceAir);
		//std::cout << start << " " << target << " " << distanceAir << std::endl;
		startCity = getCityByName(start);
		targetCity = getCityByName(target);

		startCity->addNeighbor(targetCity, distanceAir);
	}

	int numberOfQueries = 0;
	fscanf_s(file, "%d", &numberOfQueries);
	String str1, str2;

	//std::cout << numberOfQueries << std::endl;
	checkRoads();

	//printCities();

	for (int i = 0; i < numberOfQueries; i++)
	{
		fscanf_s(file, "%s %s", start, 100, target, 100);
		std::cout << start << " " << target << "c" << std::endl;
		str1 = start;
		str2 = target;
		findShortestPath(str1, str2);
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
	for (int i = 0; i < this->cityPointsX.getSize(); i++)
	{
		positionX = this->cityPointsX[i];
		positionY = this->cityPointsY[i];
		this->cities.pushBack(new City(getCityName(positionX, positionY), positionX, positionY));
	}

	// loading airlines
	int numberOfAirlines, distanceAir;
	char start[100], target[100];
	City* startCity, * targetCity;
	scanf_s("%d", &numberOfAirlines);

	for (int i = 0; i < numberOfAirlines; i++)
	{
		scanf_s("%s %s %d", start, 100, target, 100, &distanceAir);
		//std::cout << start << " " << target << " " << distanceAir << std::endl;
		startCity = getCityByName(start);
		targetCity = getCityByName(target);

		startCity->addNeighbor(targetCity, distanceAir);
	}
}

String Map::getCityName(int positionX, int positionY)
{
	String name = "";
	int pointerPosX = positionX, pointerPosY = positionY;

	// nazwa z prawej
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
	// nazwa z lewej
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
	// nazwa u góry
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
	// nazwa z do³u
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
	// nazwa w górnym prawym rogu
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
	// nazwa w dolnym prawym rogu
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
	// nazwa w górnym lewym rogu
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
	// nazwa w dolnym lewym rogu
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
	for (int i = 0; i < this->cities.getSize(); i++)
	{
		if (this->cities[i]->getName().equal(name.c_str()))
		{
			return this->cities[i];
		}
	}

	std::cout << "Blad" << std::endl;
	return nullptr;
}

City* Map::getCityByName(char* name)
{
	for (int i = 0; i < this->cities.getSize(); i++)
	{
		//std::cout << this->cities[i]->getName().c_str() << std::endl;
		if (this->cities[i]->getName().equal(name))
		{
			return this->cities[i];
		}
	}

	std::cout << "Blad" << std::endl;
	return nullptr;
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
			}

			if (currentX < this->width - 1 && this->intMap[currentX + 1][currentY] == 0 && this->charMap[currentX + 1][currentY] == '#')
			{
				this->intMap[currentX + 1][currentY] = this->intMap[currentX][currentY] + 1;
				pointsX.pushBack(currentX + 1);
				pointsY.pushBack(currentY);
			}

			if (currentY > 0 && this->intMap[currentX][currentY - 1] == 0 && this->charMap[currentX][currentY - 1] == '#')
			{
				this->intMap[currentX][currentY - 1] = this->intMap[currentX][currentY] + 1;
				pointsX.pushBack(currentX);
				pointsY.pushBack(currentY - 1);
			}

			if (currentY < this->height - 1 && this->intMap[currentX][currentY + 1] == 0 && this->charMap[currentX][currentY + 1] == '#')
			{
				this->intMap[currentX][currentY + 1] = this->intMap[currentX][currentY] + 1;
				pointsX.pushBack(currentX);
				pointsY.pushBack(currentY + 1);
			}
		}

		//std::cout << currentCity->getName().c_str() << std::endl;
		//printMap();
		zeroIntMap();
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

void Map::findShortestPath(String& start, String& target)
{
	int* distances = new int[this->cities.getSize()];
	bool visited = false;
	City* startCity = getCityByName(start);
	City* targetCity = getCityByName(target);
	Vector<City*> previous;
	//String* shortestPath = new String[this->cities.getSize()];
	PriorityQueue priorQueue;

	for (int i = 0; i < this->cities.getSize(); i++)
	{
		distances[i] = 1000000;
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
			if (previous[i]->getName().equal(currentNode.city->getName().c_str()))
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
			int index = getIndexOfCity(curNeigh->city->getName());
			int newDistance = currentNode.distance + curNeigh->distance;
			if (newDistance < distances[index])
			{
				distances[index] = newDistance;
				ListOfNeighbors newNeigh = ListOfNeighbors();
				newNeigh.city = curNeigh->city;
				newNeigh.distance = newDistance;
				newNeigh.nextNode = nullptr;
				priorQueue.push(newNeigh);
			}

			curNeigh = curNeigh->nextNode;
		}
	}

	std::cout << distances[getIndexOfCity(target)] << std::endl;
	delete[] distances;
}

void Map::zeroIntMap()
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			this->intMap[i][j] = 0;
		}
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