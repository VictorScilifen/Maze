#include "player.h"

Player::Player(Point _position, Point _direction, Point _camera_axis)
	:position(_position), direction(_direction), camera_axis(_camera_axis) {}

void Player::TurnLeft()
{
	Point end;
	end.x = direction.x * cos(ANGULAR_STEP) - direction.y * sin(ANGULAR_STEP);
	end.y = direction.x * sin(ANGULAR_STEP) + direction.y * cos(ANGULAR_STEP);
	direction = end;
	end.x = camera_axis.x * cos(ANGULAR_STEP) - camera_axis.y * sin(ANGULAR_STEP);
	end.y = camera_axis.x * sin(ANGULAR_STEP) + camera_axis.y * cos(ANGULAR_STEP);
	camera_axis = end;
}

void Player::TurnRight()
{
	Point end;
	end.x = direction.x * cos(-ANGULAR_STEP) - direction.y * sin(-ANGULAR_STEP);
	end.y = direction.x * sin(-ANGULAR_STEP) + direction.y * cos(-ANGULAR_STEP);
	direction = end;
	end.x = camera_axis.x * cos(-ANGULAR_STEP) - camera_axis.y * sin(-ANGULAR_STEP);
	end.y = camera_axis.x * sin(-ANGULAR_STEP) + camera_axis.y * cos(-ANGULAR_STEP);
	camera_axis = end;
}

void Player::GoForword(int** map)
{
	Point p = { position.x + RADIUS_STEP * direction.x ,position.y + RADIUS_STEP * direction.y };
	if (map[(int)p.x][(int)p.y] != 0) return;
	else position = p;
}

void Player::GoBackword(int** map)
{
	Point p = { position.x - RADIUS_STEP * direction.x ,position.y - RADIUS_STEP * direction.y };
	if (map[(int)p.x][(int)p.y] != 0) return;
	else position = p;
}

Point Player::get_position()
{
	return position;
}

Point Player::get_direction()
{
	return direction;
}

Point Player::get_cam() { return camera_axis; }