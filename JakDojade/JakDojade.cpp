#include <iostream>
#include "Vector.h"
#include "Map.h"
#include "City.h"

using namespace std;

void test()
{
    int height, width;
    cin >> width >> height;
    getchar();

    Map map(width, height);
    map.loadMap();
}

int main()
{
    test();
}
