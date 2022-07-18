#ifndef RENDERER_H
#define RENDERER_H

#include <graphics.h>
#include <vector>
#include "maze_map.h"

void InitRenderer();
void Render2DWalls(Point player_position, Point player_direction, std::vector<Point> visible_points);
int EuclidDistance(Point _start, Point _end);

#endif // RENDERER_H