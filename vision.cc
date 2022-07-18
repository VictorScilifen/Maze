#include "vision.h"

// given a start POINT and an end POINT
// use Bresenham to make a line,
// return route
std::vector<Point> FindRoute(Point start, Point end);

std::vector<Point> FindRoute(Point start, Point end) {
	std::vector<Point> route;
	int x = start.x;
	int y = start.y;
	int dx = abs(end.x - start.x);
	int dy = abs(end.y - start.y);
	int s1 = end.x > start.x ? 1 : -1;
	int s2 = end.y > start.y ? 1 : -1;
	bool interchange = false;	// 默认不互换 dx、dy
	if (dy > dx)				// 当斜率大于 1 时，dx、dy 互换
	{
		int temp = dx;
		dx = dy;
		dy = temp;
		interchange = true;
	}
	int p = 2 * dy - dx;
	for (int i = 0; i < dx; i++)
	{
		route.push_back({ x, y });
		if (p >= 0)
		{
			if (!interchange)		// 当斜率 < 1 时，选取上下象素点
				y += s2;
			else					// 当斜率 > 1 时，选取左右象素点
				x += s1;
			p -= 2 * dx;
		}
		if (!interchange)
			x += s1;				// 当斜率 < 1 时，选取 x 为步长
		else
			y += s2;				// 当斜率 > 1 时，选取 y 为步长
		p += 2 * dy;
	}
	return route;
}


Point FindNearestPoint(Point position, Point direction, int** map)
{
	Point end = { direction.x + position.x, direction.y + position.y };
	std::vector<Point> route = FindRoute(position, end);
	for (auto ptr = route.begin(); ptr != route.end(); ++ptr) {
		// possible overflow
		if (map[ptr->x][ptr->y] == 1)
			return *ptr;
	}
	return end;
}