#include "City.h"

City::City(String& name)
{
    this->name = name;
    this->listOfNeighbors = nullptr;
}

City::City(String&& name)
{
    this->name = name;
    this->listOfNeighbors = nullptr;
}

String& City::getName()
{
    return this->name;
}

void City::addNeighbor(String& name, int distance)
{
    ListOfNeighbors* newNode = new ListOfNeighbors;
    newNode->name = name;
    newNode->distance = distance;
    newNode->nextNode = nullptr;

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

void City::printNeighbors()
{
    std::cout << "Name: " << this->name.c_str() << std::endl;
    std::cout << "Neighbors:" << std::endl;

    ListOfNeighbors* currentNode = this->listOfNeighbors;
    while (currentNode != nullptr)
    {
        std::cout << currentNode->name.c_str() << " " << currentNode->distance << std::endl;
        currentNode = currentNode->nextNode;
    }
}
