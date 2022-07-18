#include <conio.h>

#include "maze_map.h"
#include "player.h"
#include "renderer.h"

int main()
{
	MazeMap maze;
	maze.set_borders();
	maze.PrintMap();
	Player player({ 25,25 }, maze.get_map());
	InitRenderer();
	Render2DWalls(player.get_position(), player.get_direction(), player.get_visible_points());
	while (1) {
		char c = _getch();
		switch (c) {
		case 'a':
			player.TurnLeft();
			Render2DWalls(player.get_position(), player.get_direction(), player.get_visible_points());
			break;
		case 'd':
			player.TurnRight();
			Render2DWalls(player.get_position(), player.get_direction(), player.get_visible_points());
			break;
		case 'w':
			player.GoForword();
			Render2DWalls(player.get_position(), player.get_direction(), player.get_visible_points());
			break;
		case 's':
			player.GoBackword();
			Render2DWalls(player.get_position(), player.get_direction(), player.get_visible_points());
			break;
		default:
			Render2DWalls(player.get_position(), player.get_direction(), player.get_visible_points());
		}
	}
	std::cout << EuclidDistance({ 25,25 }, { 0,13 });
}