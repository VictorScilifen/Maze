#include "renderer.h"

// return the height
//int RayCasting(Point ray_start, Point cam_dir, Point ray_direction, int** world);
void RayCasting(Point ray_start, Point cam_dir, Point ray_direction, int** world);
// DDA algorithm used along X-axis
// return distance
Point XAxisDDA(Point start, Point dir, int** map);
// DDA algorithm used along Y-axis
//return distance
Point YAxisDDA(Point start, Point dir, int** map);
double EuclidDistance(Point _start, Point _end);
int DistanceToHeight(double distance);

void InitRenderer() {
	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);
}

void Render2DWalls(Player player, int** world) {
	cleardevice();
	for (int i = 0; i < WINDOW_WIDTH; i++) {
		double ray_dir_x = (i * 2.0 / WINDOW_WIDTH - 1.0000) * player.get_cam().x + player.get_direction().x;
		double ray_dir_y = (i * 2.0 / WINDOW_WIDTH - 1.0000) * player.get_cam().y + player.get_direction().y;
		//int wall_height = RayCasting(player.get_position(), player.get_cam(), { ray_dir_x, ray_dir_y }, world);
		RayCasting(player.get_position(), player.get_cam(), { ray_dir_x, ray_dir_y }, world);
		//line(i, HORIZON_HEIGHT - wall_height / 2, i, HORIZON_HEIGHT + wall_height / 2);
		//Sleep(500);
	}
}

void RenderCeiling() {

}

void RenderFloor() {

}

void RayCasting(Point ray_start, Point cam_dir, Point ray_dir, int** world) {
	double euclidian_distance;
	double perp_distance;
	/*setlinecolor(BLUE);
	line(20 * (XAxisDDA(ray_start, ray_dir, world).x - ray_start.x) + 240,
		-20 * (XAxisDDA(ray_start, ray_dir, world).y - ray_start.y) + 280, 240, 280);
	setlinecolor(RED);
	line(20 * (YAxisDDA(ray_start, ray_dir, world).x - ray_start.x) + 720,
		-20 * (YAxisDDA(ray_start, ray_dir, world).y - ray_start.y) + 280, 720, 280);*/
	if (XAxisDDA(ray_start, ray_dir, world).magnitue() <= YAxisDDA(ray_start, ray_dir, world).magnitue())
	{
		//euclidian_distance = XAxisDDA(ray_start, ray_dir, world);
		setlinecolor(BLUE);
		line(20 * (XAxisDDA(ray_start, ray_dir, world).x - ray_start.x) + 480,
			-20 * (XAxisDDA(ray_start, ray_dir, world).y - ray_start.y) + 280, 480, 280);
	}
	else
	{
		//euclidian_distance = YAxisDDA(ray_start, ray_dir, world);
		setlinecolor(RED);
		line(20 * (YAxisDDA(ray_start, ray_dir, world).x - ray_start.x) + 480,
			-20 * (YAxisDDA(ray_start, ray_dir, world).y - ray_start.y) + 280, 480, 280);
	}
	//perp_distance = euclidian_distance * sin(acos(ray_dir * cam_dir / (ray_dir.magnitue() * cam_dir.magnitue())));
	//return DistanceToHeight(perp_distance);
}

Point XAxisDDA(Point start, Point dir, int** map) {
	double side_x, side_y, distance;
	int map_x = (int)start.x, map_y = (int)start.y;
	int dda_count = 0;
	// straight up or down
	if (abs(dir.x - 0) < 0.0001) {
		if (dir.y > 0) { // straight to down
			side_y = start.y - (int)start.y;
			distance = side_y;
			start.y -= side_y;
			while (dda_count < MAZE_SIZE) {
				start.y--;
				map_y--;
				distance++;
				if (map[map_x][map_y] != 0) {
					return{ start.x,start.y };
					//return distance;
				}
				dda_count++;
			}
			return{ start.x,start.y };
			//return distance;
		}
		else {
			side_y = (int)start.y + 1 - start.y;
			distance = side_y;
			start.y += side_y;
			while (dda_count < MAZE_SIZE) {
				start.y++;
				map_y++;
				distance++;
				if (map[map_x][map_y] != 0) {
					return{ start.x,start.y };
					//return distance;
				}
				dda_count++;
			}
			return{ start.x,start.y };
			//return distance;
		}

	}
	if (abs(atan2(dir.y, dir.x)) < PI / 2) { // point to the right
		side_x = (int)start.x + 1 - start.x;
		side_y = side_x * tan(atan2(dir.y, dir.x));
		distance = side_x / cos(atan2(dir.y, dir.x));
		start.x = (int)start.x + 1;
		start.y += side_y;
		while (dda_count < MAZE_SIZE) {
			//start.x = start.x <0 ? 0 : start.x>MAZE_SIZE ? MAZE_SIZE - 1 : start.x;
			//start.y = start.y <0 ? 0 : start.y>MAZE_SIZE ? MAZE_SIZE - 1 : start.y;
			if (map[map_x][map_y] != 0) {
				return{ start.x,start.y };
				//return distance;
			}
			start.x++;
			map_x++;
			start.y += (dir.y / dir.x);
			distance += abs(1.0 / cos(atan2(dir.y, dir.x)));
			dda_count++;
		}
		return{ start.x,start.y };
		//return distance;
	}
	else { // point to the left
		side_x = start.x - (int)start.x;
		side_y = side_x * tan(atan2(dir.y, dir.x));
		distance = side_x / cos(atan2(dir.y, dir.x));
		start.x = (int)start.x;
		start.y += side_y;
		while (dda_count < MAZE_SIZE) {
			//start.x = start.x <0 ? 0 : start.x>MAZE_SIZE ? MAZE_SIZE - 1 : start.x;
			//start.y = start.y <0 ? 0 : start.y>MAZE_SIZE ? MAZE_SIZE - 1 : start.y;
			if (map[map_x][map_y] != 0) {
				return{ start.x,start.y };
				//return distance;
			}
			start.x--;
			map_x--;
			start.y -= (dir.y / dir.x);
			distance += abs(1.0 / cos(atan2(dir.y, dir.x)));
			dda_count++;
		}
		return{ start.x,start.y };
		//return distance;
	}
}

Point YAxisDDA(Point start, Point dir, int** map) {
	double side_x, side_y, distance;
	int map_x = (int)start.x, map_y = (int)start.y;
	int dda_count = 0;
	// straight left or right
	if (abs(dir.y - 0) < 0.0001) {
		if (dir.x < 0) { // straight to left
			side_x = start.x - (int)start.x;
			distance = side_x;
			start.x -= side_x;
			while (dda_count < MAZE_SIZE) {
				map_x--;
				distance++;
				if (map[map_x][map_y] != 0) {
					return{ start.x,start.y };
					//return distance;
				}
				dda_count++;
			}
			return{ start.x,start.y };
			//return distance;
		}
		else {
			side_x = (int)start.x + 1 - start.x;
			distance = side_x;
			start.x = (int)start.x + 1;
			while (dda_count < MAZE_SIZE) {
				map_x++;
				distance++;
				if (map[map_x][map_y] != 0) {
					return{ start.x,start.y };
					//return distance;
				}
				dda_count++;
			}
			return{ start.x,start.y };
			//return distance;
		}

	}
	if (atan2(dir.y, dir.x) > 0) { // point to the up
		side_y = (int)start.y + 1 - start.y;
		side_x = side_y / tan(atan2(dir.y, dir.x));
		distance = side_y / sin(atan2(dir.y, dir.x));
		start.y = (int)start.y + 1;
		start.x += side_x;

		while (dda_count < MAZE_SIZE) {
			//start.x = start.x <0 ? 0 : start.x>MAZE_SIZE ? MAZE_SIZE - 1 : start.x;
			//start.y = start.y <0 ? 0 : start.y>MAZE_SIZE ? MAZE_SIZE - 1 : start.y;
			if (map[map_x][map_y] != 0) {
				return{ start.x,start.y };
				//return distance;
			}
			map_y++;
			start.y++;
			start.x += (dir.x / dir.y);
			distance += 1.0 / sin(atan2(dir.y, dir.x));
			dda_count++;
		}
		return{ start.x,start.y };
		//return distance;
	}
	else { // point to the down
		side_y = start.y - (int)start.y;
		side_x = side_y / tan(atan2(dir.y, dir.x));
		distance = side_y / sin(atan2(dir.y, dir.x));
		start.y = (int)start.y;
		start.x += side_x;
		while (dda_count < MAZE_SIZE) {
			//start.x = start.x <0 ? 0 : start.x>MAZE_SIZE ? MAZE_SIZE - 1 : start.x;
			//start.y = start.y <0 ? 0 : start.y>MAZE_SIZE ? MAZE_SIZE - 1 : start.y;
			if (map[map_x][map_y] != 0) {
				return{ start.x,start.y };
				//return distance;
			}
			start.y--;
			map_y--;
			start.x -= (dir.x / dir.y);
			distance += abs(1.0 / sin(atan2(dir.y, dir.x)));
			dda_count++;
		}
		return{ start.x,start.y };
		//return distance;
	}
}

double EuclidDistance(Point _start, Point _end) {
	return sqrt(pow(_start.x - _end.x, 2) + pow(_start.x - _end.x, 2));
}

int DistanceToHeight(double distance) {
	return (int)(WINDOW_HEIGHT / distance);
}