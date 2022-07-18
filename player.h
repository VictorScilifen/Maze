#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "maze_map.h"
#include "vision.h"

class Player {
	Point position;
	Point direction; // the angle player head to
	std::vector<Point> directions;
	std::vector<Point> around_points; // all near points in all directions
	int** ptr_map; //player in this map
public:
	Player(Point _position, int** _ptr_map);
	void TurnLeft();
	void TurnRight();
	void GoForword();
	void GoBackword();
	Point get_position();
	Point get_direction();
	std::vector<Point> get_visible_points();
};

#endif // PLAYER_H