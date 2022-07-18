#ifndef MAZE_MAP_H
#define MAZE_MAP_H
#include <cmath>
#include <iostream>
#include "config.h"


class MazeMap {
	int** map;
public:
	MazeMap();
	~MazeMap();
	int** get_map();
	int get_point(int x, int y);
	bool set_point(int x, int y);
	bool delete_point(int x, int y);
	void set_borders();
	void PrintMap();
};

#endif // MAZE_MAP_H