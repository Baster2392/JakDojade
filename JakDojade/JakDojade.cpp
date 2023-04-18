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
    String str1("AA"), str2("BB");
    //cin >> width >> height;
    //getchar();

    Map map(33, 23);
    map.loadFromFile();
    //map.checkRoads();
    //map.printCities();
    //map.findShortestPath(str1, str2);
}

int main()
{
    test();
}
