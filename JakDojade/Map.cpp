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

	for (int i = 0; i < this->cityPointsX.getSize(); i++)
	{
		std::cout << getCityName(this->cityPointsX[i], this->cityPointsY[i]).c_str() << std::endl;
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

void Map::checkRoads()
{
	Vector<int> pointsX;
	Vector<int> pointsY;
	int posX, posY;
	int currentX, currentY;

	for (int i = 0; i < this->cityPointsX.getSize(); i++)
	{
		pointsX.pushBack(this->cityPointsX[i]);
		pointsY.pushBack(this->cityPointsY[i]);

		while (pointsX.getSize() > 0)
		{
			currentX = pointsX[0];
			currentY = pointsY[0];
			pointsX.erase(0);
			pointsY.erase(0);

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

		printMap();
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