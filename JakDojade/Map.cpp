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

void Map::loadMap()
{
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
		if (this->cities[i]->getName().c_str() == name.c_str())
		{
			return this->cities[i];
		}
	}

	std::cout << "Blad" << std::endl;
	return nullptr;
}

void Map::checkRoads()
{
	City* currentCity, *foundCity;
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
				&& currentX != currentCity->getPositionX() && currentY != currentCity->getPositionY())
			{
				foundCity = getCityAtPosition(currentX - 1, currentY);
				currentCity->addNeighbor(foundCity->getName(), this->intMap[currentX][currentY]);
			}

			if (currentX < this->width - 1 && this->intMap[currentX + 1][currentY] == 0 && this->charMap[currentX + 1][currentY] == '*'
				&& currentX != currentCity->getPositionX() && currentY != currentCity->getPositionY())
			{
				foundCity = getCityAtPosition(currentX + 1, currentY);
				currentCity->addNeighbor(foundCity->getName(), this->intMap[currentX][currentY]);
			}

			if (currentY > 0 && this->intMap[currentX][currentY - 1] == 0 && this->charMap[currentX][currentY - 1] == '*'
				&& currentX != currentCity->getPositionX() && currentY != currentCity->getPositionY())
			{
				foundCity = getCityAtPosition(currentX, currentY - 1);
				currentCity->addNeighbor(foundCity->getName(), this->intMap[currentX][currentY]);
			}

			if (currentY < this->height - 1 && this->intMap[currentX][currentY + 1] == 0 && this->charMap[currentX][currentY + 1] == '*'
				&& currentX != currentCity->getPositionX() && currentY != currentCity->getPositionY())
			{
				foundCity = getCityAtPosition(currentX, currentY + 1);
				currentCity->addNeighbor(foundCity->getName(), this->intMap[currentX][currentY]);
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