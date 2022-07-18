#ifndef PLAYER_H
#define PLAYER_H
#include <cmath>
#include <vector>
#include "config.h"

class Point {
public:
	double x;
	double y;

	double operator*(const Point p)const
	{
		return this->x * p.x + this->y * p.y;
	}
	Point operator+(const Point p)const
	{
		return { this->x + p.x,this->y + y };
	}
	Point operator-(const Point p)const
	{
		return { this->x - p.x,this->y - y };
	}
	bool operator==(const Point p)const
	{
		return this->x == p.x && this->y == p.y;
	}
	double magnitue() {
		return sqrt(x * x + y * y);
	}
};

class Player {
	Point position;
	Point direction; // the angle player head to
	Point camera_axis;
public:
	Player(Point _position, Point _direction, Point _camera_axis);
	void TurnLeft();
	void TurnRight();
	void GoForword(int** map);
	void GoBackword(int** map);
	Point get_position();
	Point get_direction();
	Point get_cam();
};

#endif // PLAYER_H