#include "player.h"
#include <set>

std::vector<Point> GenCircleDirections();

int FindIndex(Point target, std::vector<Point> sequence);

Player::Player(Point _position, int** _ptr_map)
{
	position = _position;
	ptr_map = _ptr_map;
	directions = GenCircleDirections();
	for (auto ptr = directions.begin(); ptr != directions.end(); ++ptr) {
		Point nearest_point = FindNearestPoint(position, *ptr, ptr_map);
		around_points.push_back(nearest_point);
	}
	direction = directions[0];
}

void Player::TurnLeft()
{
	// update direction
	if (direction == directions[0]) {
		direction = *(directions.end() - 1);
	}
	else {
		direction = directions[FindIndex(direction, directions) - 1];
	}
}

void Player::TurnRight()
{
	// update direction
	if (direction == *(directions.end() - 1)) {
		direction = directions[0];
	}
	else {
		direction = directions[FindIndex(direction, directions) + 1];
	}
}

void Player::GoForword()
{
	// update position
	int x = position.x;
	int y = position.y;
	int dx = abs(direction.x - position.x);
	int dy = abs(direction.y - position.y);
	int s1 = direction.x > position.x ? 1 : -1;
	int s2 = direction.y > position.y ? 1 : -1;
	bool interchange = false;	// 默认不互换 dx、dy
	if (dy > dx)				// 当斜率大于 1 时，dx、dy 互换
	{
		int temp = dx;
		dx = dy;
		dy = temp;
		interchange = true;
	}
	int p = 2 * dy - dx;
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
	position = { x,y };
	// update around_points
	around_points.clear();
	for (auto ptr = directions.begin(); ptr != directions.end(); ++ptr) {
		Point nearest_point = FindNearestPoint(position, *ptr, ptr_map);
		around_points.push_back(nearest_point);
	}
}

void Player::GoBackword()
{
	// update position
	int x = position.x;
	int y = position.y;
	int dx = abs(-direction.x - position.x);
	int dy = abs(-direction.y - position.y);
	int s1 = -direction.x > position.x ? 1 : -1;
	int s2 = -direction.y > position.y ? 1 : -1;
	bool interchange = false;	// 默认不互换 dx、dy
	if (dy > dx)				// 当斜率大于 1 时，dx、dy 互换
	{
		int temp = dx;
		dx = dy;
		dy = temp;
		interchange = true;
	}
	int p = 2 * dy - dx;
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
	position = { x,y };
	// update around_points
	around_points.clear();
	for (auto ptr = directions.begin(); ptr != directions.end(); ++ptr) {
		Point nearest_point = FindNearestPoint(position, *ptr, ptr_map);
		around_points.push_back(nearest_point);
	}
}

Point Player::get_position()
{
	return position;
}

Point Player::get_direction()
{
	return direction;
}

// given the direction of the player and the points around player
// return points in players's vision field
// use loop list to cut around_points
std::vector<Point> Player::get_visible_points()
{
	std::vector<Point> visible_points;
	int d_size = size(directions);
	int direction_index = FindIndex(direction, directions);
	int range = PLAYER_FIELD / 360.0 * d_size;
	if (direction_index - range < 0 && direction_index + range <= d_size)
	{
		visible_points.assign(around_points.end() - range + direction_index, around_points.end());
		for (auto ptr = around_points.begin();
			ptr != around_points.begin() + direction_index + range;
			++ptr)
		{
			visible_points.push_back(*ptr);
		}
	}
	else if (direction_index + range > d_size)
	{
		visible_points.assign(around_points.begin() + direction_index - range, around_points.end());
		for (auto ptr = around_points.begin();
			ptr != around_points.begin() + range - (d_size - direction_index);
			++ptr)
		{
			visible_points.push_back(*ptr);
		}
	}
	else
	{
		visible_points.assign(around_points.begin() + direction_index - range,
			around_points.begin() + direction_index + range);
	}
	return visible_points;
}

// generate 564 angle-points to refer the different angle 
std::vector<Point> GenCircleDirections()
{
	int x = 0, y = 0, r = 100;
	int tx = 0, ty = r, d = 3 - 2 * r;
	std::vector<Point> directions;
	while (tx <= ty)
	{
		// 利用圆的八分对称性画点
		directions.push_back({ x + tx,y + ty });
		directions.push_back({ x + tx,y - ty });
		directions.push_back({ x - tx,y + ty });
		directions.push_back({ x - tx,y - ty });
		directions.push_back({ x + ty,y + tx });
		directions.push_back({ x + ty,y - tx });
		directions.push_back({ x - ty,y + tx });
		directions.push_back({ x - ty,y - tx });

		if (d < 0)		// 取上面的点
			d += 4 * tx + 6;
		else			// 取下面的点
			d += 4 * (tx - ty) + 10, ty--;
		tx++;
	}
	std::set<Point, PointOperator> s{ directions.begin(),directions.end() };
	directions.assign(s.begin(), s.end());
	return directions;
}

int FindIndex(Point target, std::vector<Point> sequence)
{
	int index = 0;
	for (auto ptr = sequence.begin(); ptr != sequence.end(); ++ptr) {
		if (target == *ptr) return index;
		index++;
	}
	return index;
}
