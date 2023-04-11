#include <iostream>
#include "Vector.h"
#include "Map.h"
#include "City.h"

using namespace std;

struct Cords {
    int x;
    int y;
};

void add(Vector<Cords>& v)
{
    Cords cord1;
    Cords cord2;
    cord1.x = 1;
    cord1.y = 2;
    cord2.x = 23;
    cord2.y = 12;
    v.pushBack(cord1);
    v.pushBack(cord2);
}

void test()
{
    int height, width;
    cin >> width >> height;
    getchar();

    Map map(width, height);
    map.loadMap();
    map.checkRoads();
}

int main()
{
    test();
}
