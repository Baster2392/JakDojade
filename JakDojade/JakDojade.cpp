#include <iostream>
#include "Vector.h"
#include "Map.h"
#include "City.h"
#include "HashMap.h"

using namespace std;

void init()
{
    int height, width;
    cin >> width >> height;
    getchar();

    Map map(width, height);
    map.loadMap();
}

int main()
{
    init();
}
