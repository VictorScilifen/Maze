#include <conio.h>

#include "maze_map.h"
#include "player.h"
#include "renderer.h"

int main()
{
	MazeMap maze;
	maze.set_borders();
	for (int i = 5; i <= 15; i++) {
		maze.set_point(5, i);
		maze.set_point(i, 5);
		//maze.set_point(15, i);
		maze.set_point(i, 15);
	}
	maze.PrintMap();
	_getch();
	Player player({ 10,10 }, { 0,1 }, { 0.667,0 });
	InitRenderer();
	Render2DWalls(player, maze.get_map());
	while (1) {
		char c = _getch();
		switch (c) {
		case 'a':
			player.TurnLeft();
			Render2DWalls(player, maze.get_map());
			break;
		case 'd':
			player.TurnRight();
			Render2DWalls(player, maze.get_map());
			break;
		case 'w':
			player.GoForword(maze.get_map());
			Render2DWalls(player, maze.get_map());
			break;
		case 's':
			player.GoBackword(maze.get_map());
			Render2DWalls(player, maze.get_map());
			break;
		default:
			Render2DWalls(player, maze.get_map());
		}
	}
}