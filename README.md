Title:
JakDojade

How it works?
Application read maps written in .txt files by following rules:
- '#' - road from one town to another. It means 1 unit of lenght
- '*' - town, near this symbol, should occur name of town
- '.' - empty space

Map may included airline connections, which are additional connections between towns. 
This is example:
1
TOWN1 TOWN2 26
Where 26 is distance between towns, comparable with distance read from map and 1 is number of airlines to read.

Appplication parse file and build map of neighbours. In second step we can write a query and ask application what is shortest path between two towns.
Example of query:
TOWN1 TOWN2 0
Where number at end is mode in which application give us result:
0 - write only length of shortest path
1 - additionaly write sequence of towns which we have to visit in our shortest path

Example of full .txt file which can be parsed in application:
```
20 20
.........GDANSK.....
........*...........
........#...........
........#...........
*##################.
#SZCZECIN.........#.
#.................#.
##................#.
.############*#####.
.#...WARSZAWA.......
.#..................
.#############......
.#...........#......
.#..WROCLAW.##......
.#..*.......*.......
.####.......#KIELCE.
......*##.#########.
.OPOLE..#.*.......#.
........#.KRAKOW..#.
........###########.
0
3
KIELCE KRAKOW 0
KRAKOW GDANSK 0
KRAKOW GDANSK 1
```
