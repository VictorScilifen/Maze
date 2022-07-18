#ifndef VISION_H
#define VISION_H

#include <vector>
#include "maze_map.h"

// given position and direction of one POINT,
// return the coordinate of the nearest POINT
// Point FindNearestPoint(Point position, Point direction, int map[MAZE_SIZE][MAZE_SIZE]);
Point FindNearestPoint(Point position, Point direction, int** map);


#endif // VISION_H