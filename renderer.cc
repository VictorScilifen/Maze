#include "renderer.h"

int ManhattanDistance(Point _start, Point _end);
double NormalDistance(Point _start, Point _normal, Point _end);

int DistanceToHeight(double distance);

void InitRenderer() {
	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);
}

void Render2DWalls(Point player_position, Point player_direction, std::vector<Point> visible_points) {
	cleardevice();
	std::vector<int> heights;
	for (auto ptr = visible_points.begin();
		ptr != visible_points.end();
		++ptr) {
		// heights.push_back(DistanceToHeight(ManhattanDistance(player_position, *ptr)));
		heights.push_back(DistanceToHeight(NormalDistance(player_position, player_direction, *ptr)));
	}
	int block_index = 1;
	int block_width = 1.0 * WINDOW_WIDTH / size(heights);
	for (auto ptr = heights.begin();
		ptr != heights.end();
		++ptr)
	{
		for (int i = 0; i <= block_width; i++)
		{
			line(i + block_index * block_width, HORIZON_HEIGHT + (*ptr) / 2,
				i + block_index * block_width, HORIZON_HEIGHT - (*ptr) / 2);
		}
		block_index++;
	}
	Sleep(8);
}

int ManhattanDistance(Point _start, Point _end) {
	return abs(_end.x - _start.x) + abs(_end.y - _start.y);
}

int EuclidDistance(Point _start, Point _end) {
	return (int)sqrt(pow(_start.x - _end.x, 2) + pow(_start.x - _end.x, 2));
}

// given a vector, draw the normal line, cal the distance
// between end point and this normal line.
double NormalDistance(Point _start, Point _normal, Point _end) {
	double A = _normal.x;
	double B = _normal.y;
	double C = -(A * _start.x + B * _start.y);
	return (abs(A * _end.x + B * _end.y + C)) / (sqrt(A * A + B * B));
}

int DistanceToHeight(double distance) {
	return (int)(WINDOW_HEIGHT / distance);
}