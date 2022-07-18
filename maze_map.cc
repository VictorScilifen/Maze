#include "maze_map.h"

MazeMap::MazeMap()
{
	map = new int* [MAZE_SIZE];
	for (int i = 0; i < MAZE_SIZE; i++) {
		map[i] = new int[MAZE_SIZE];
	}
	for (int i = 0; i < MAZE_SIZE; i++) {
		for (int j = 0; j < MAZE_SIZE; j++) {
			map[i][j] = 0;
		}
	}
}

MazeMap::~MazeMap()
{
	if (map) {
		for (int i = 0; i < MAZE_SIZE; i++) {
			delete map[i];
			map[i] = NULL;
		}
		delete map;
	}
}

int** MazeMap::get_map()
{
	return map;
}

int MazeMap::get_point(int x, int y)
{
	return map[x][y];
}

bool MazeMap::set_point(int x, int y)
{
	map[x][y] = 1;
	return true;
}

bool MazeMap::delete_point(int x, int y)
{
	map[x][y] = 0;
	return true;
}

void MazeMap::set_borders()
{
	for (int i = 0; i < MAZE_SIZE; i++) {
		map[0][i] = 1;
		map[i][0] = 1;
		map[MAZE_SIZE - 1][i] = 1;
		map[i][MAZE_SIZE - 1] = 1;
	}
}

void MazeMap::PrintMap()
{
	for (int i = MAZE_SIZE - 1; i >= 0; i--) {
		for (int j = 0; j < MAZE_SIZE; j++) {
			std::cout << map[j][i] << ' ';
		}
		std::cout << std::endl;
	}
}


bool PointOperator::operator()(const Point& p1, const Point& p2) const
{
	return atan2(p1.y, p1.x) > atan2(p2.y, p2.x);
}