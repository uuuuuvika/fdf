#include "fdf.h"

double get_pix_position(int x1, int x2, int y1, int y2, int x_cur, int y_cur)
{
	double full_dist = hypot(x2 - x1, y2 - y1);
	double dist_to_current = hypot(x_cur - x1, y_cur - y1);
	if (full_dist != 0.0)
		return (dist_to_current / full_dist);
	return 1.0;
}

void draw_l(t_img *img, int x1, int y1, int x2, int y2, t_color color1, t_color color2)
{
	int x1_start = x1;
	int y1_start = y1;//
	//printf("x1: %d, y1: %d, x2: %d, y2: %d\n", x1, y1, x2, y2);

	int dx = abs(x2 - x1);//10, 5 = 5
	int dy = abs(y2 - y1);//0, -5 = 5
	int sx = (x1 < x2) ? 1 : -1; // 1
	int sy = (y1 < y2) ? 1 : -1; // -1
	int err = dx - dy; //0
	int err2;
	int r, g, b;
	double position;
	

	while (!(x1 == x2 && y1 == y2))
	{
		if (x1 >= 0 && x1 <= WIDTH && y1 >= 0 && y1 <= HEIGHT)
		{
			position = get_pix_position(x1_start, x2, y1_start, y2, x1, y1);
			r = round(color1.r * (1 - position) + color2.r * position);
			g = round(color1.g * (1 - position) + color2.g * position);
			b = round(color1.b * (1 - position) + color2.b * position);

			int color = (r << 16) | (g << 8) | b;
			img_pix_put(img, x1, y1, color);
		}

		err2 = 2 * err; //0
		if (err2 > -dy) //yes
		{
			err -= dy; // -5
			x1 += sx; //x1 + 1 = 6
		}
		if (err2 < dx) //yes
		{
			err += dx; // -5 + 5 = 0
			y1 += sy; // y1 -1 = 4
		}
		// if (prevX != x1 && prevY != y1)
		// {
		// 	color = (r << 24) | (g << 16) | (b << 8) | 128;
		// 	img_pix_put(img, prevX + sx, prevY, color);
		// 	img_pix_put(img, prevX, prevY + sy, color);

		// 	printf("prevX: %d, x1: %d\n", prevX, x1);

		// 	printf("prevY: %d, y1: %d\n", prevY, y1);

		
		// }
		// else if (prevX != x1 && prevY == y1)
		// 	img_pix_put(img, x1, prevY, color);
		// else if (prevY != y1)
		// 	img_pix_put(img, prevX, y1, color);
	}
}

void draw_lines(t_img *img, t_map *map)
{
	int x;
	int y;
	double nx_next;
	double ny_next;
	double nx;
	double ny;

	x = 0;
	while (x < map->num_rows)
	{
		y = 0;
		while (y < map->num_cols)
		{
			nx = map->coords[x][y].x_iso + WIDTH / 2;
			ny = map->coords[x][y].y_iso + HEIGHT / 2;
			t_color color = map->coords[x][y].color;

			if (x < map->num_rows - 1)
			{
				nx_next = map->coords[x + 1][y].x_iso + WIDTH / 2;
				ny_next = map->coords[x + 1][y].y_iso + HEIGHT / 2;
				//printf("nx: %f, ny: %f, nx_next: %f, ny_next: %f\n", nx, ny, nx_next, ny_next);
				t_color color_next = map->coords[x + 1][y].color;
				draw_l(img, nx, ny, nx_next, ny_next, color, color_next);
				// drawLine(img, nx, ny, nx_next, ny_next, color, color_next);
			}
			if (y < map->num_cols - 1)
			{
				nx_next = map->coords[x][y + 1].x_iso + WIDTH / 2;
				ny_next = map->coords[x][y + 1].y_iso + HEIGHT / 2;
				t_color color_next = map->coords[x][y + 1].color;
				draw_l(img, nx, ny, nx_next, ny_next, color, color_next);
				// drawLine(img, nx, ny, nx_next, ny_next, color, color_next);
			}
			y++;
		}
		x++;
	}
}