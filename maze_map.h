#ifndef MAZE_MAP_H
#define MAZE_MAP_H
#include <cmath>
#include <iostream>
#include "config.h"

class Point {
public:
	int x, y;

	// redefine operator ==
	bool operator==(const Point p)const {
		return (this->x == p.x && this->y == p.y);
	}
};

class PointOperator {
public:
	bool operator()(const Point& p1, const Point& p2)const;
};


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