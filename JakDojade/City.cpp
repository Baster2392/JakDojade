#include "City.h"

City::City(String& name, int positionX, int positionY)
{
    this->name = name;
    this->listOfNeighbors = nullptr;
    this->numberOfNeighbors = 0;
    this->positionX = positionX;
    this->positionY = positionY;
}

City::City(String&& name, int positionX, int positionY)
{
    this->name = name;
    this->listOfNeighbors = nullptr;
    this->numberOfNeighbors = 0;
    this->positionX = positionX;
    this->positionY = positionY;
}

City::~City()
{
    ListOfNeighbors* currentNode = this->listOfNeighbors;
    ListOfNeighbors* toDelete = this->listOfNeighbors;
    while (currentNode != nullptr)
    {
        toDelete = currentNode;
        currentNode = currentNode->nextNode;
        delete toDelete;
    }
}

String& City::getName()
{
    return this->name;
}

int City::getPositionX()
{
    return this->positionX;
}

int City::getPositionY()
{
    return this->positionY;
}

int City::getNumberOfNeighbors()
{
    return this->numberOfNeighbors;
}

void City::addNeighbor(City* city, int distance)
{
    ListOfNeighbors* newNode = new ListOfNeighbors;
    newNode->city = city;
    newNode->distance = distance;
    newNode->nextNode = nullptr;
    this->numberOfNeighbors++;

    if (this->listOfNeighbors == nullptr)
    {
        this->listOfNeighbors = newNode;
        return;
    }

    ListOfNeighbors* currentNode = this->listOfNeighbors;

    if (currentNode == this->listOfNeighbors && currentNode->distance > distance)
    {
        newNode->nextNode = this->listOfNeighbors;
        this->listOfNeighbors = newNode;
        return;

    }

    while (currentNode != nullptr)
    {
        if (currentNode->nextNode == nullptr)
        {
            currentNode->nextNode = newNode;
            return;
        }
        else
        {
            if (currentNode->nextNode->distance > distance)
            {
                newNode->nextNode = currentNode->nextNode;
                currentNode->nextNode = newNode;
                return;
            }
        }

        currentNode = currentNode->nextNode;
    }
}

ListOfNeighbors* City::getSmallestVertex()
{
    return this->listOfNeighbors;
}

void City::printNeighbors()
{
    //std::cout << "Name: " << this->name.c_str() << std::endl;
    std::cout << "Neighbors:" << std::endl;

    ListOfNeighbors* currentNode = this->listOfNeighbors;
    while (currentNode != nullptr)
    {
        std::cout << currentNode->city->getName().c_str() << " " << currentNode->distance << std::endl;
        currentNode = currentNode->nextNode;
    }

    std::cout << std::endl;
}
