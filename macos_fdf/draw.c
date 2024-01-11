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
	int y1_start = y1;

	int dx = abs(x2 - x1);
	int dy = abs(y2 - y1);
	int sx = (x1 < x2) ? 1 : -1;
	int sy = (y1 < y2) ? 1 : -1;
	int err = dx - dy;
	int err2;
	int r, g, b, color;
	double position;

	while (!(x1 == x2 && y1 == y2))
	{
		if (x1 >= 0 && x1 <= WIDTH && y1 >= 0 && y1 <= HEIGHT)
		{
			position = get_pix_position(x1_start, x2, y1_start, y2, x1, y1);
			r = round(color1.r * (1 - position) + color2.r * position);
			g = round(color1.g * (1 - position) + color2.g * position);
			b = round(color1.b * (1 - position) + color2.b * position);
			color = (r << 16) | (g << 8) | b;
			img_pix_put(img, x1, y1, color);
		}
		err2 = 2 * err;
		if (err2 > -dy)
		{
			err -= dy;
			x1 += sx;
		}
		if (err2 < dx)
		{
			err += dx;
			y1 += sy;
		}
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