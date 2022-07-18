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
	bool interchange = false;	// Ĭ�ϲ����� dx��dy
	if (dy > dx)				// ��б�ʴ��� 1 ʱ��dx��dy ����
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
			if (!interchange)		// ��б�� < 1 ʱ��ѡȡ�������ص�
				y += s2;
			else					// ��б�� > 1 ʱ��ѡȡ�������ص�
				x += s1;
			p -= 2 * dx;
		}
		if (!interchange)
			x += s1;				// ��б�� < 1 ʱ��ѡȡ x Ϊ����
		else
			y += s2;				// ��б�� > 1 ʱ��ѡȡ y Ϊ����
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