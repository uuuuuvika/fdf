#include "fdf.h"

float get_pix_position(int x1, int x2, int y1, int y2, int x_cur, int y_cur)
{
	float full_dist = hypot(x2 - x1, y2 - y1);
	float dist_to_current = hypot(x_cur - x1, y_cur - y1);
	if (full_dist != 0.0)
		return (dist_to_current / full_dist);
	return 1.0;
}

void draw_l(t_img *img, int x1, int y1, int x2, int y2, t_color color1, t_color color2)
{
	int x1_start = x1;
	int y1_start = y1; //
	// printf("x1: %d, y1: %d, x2: %d, y2: %d\n", x1, y1, x2, y2);

	int dx = abs(x2 - x1);		 // 10, 5 = 5
	int dy = abs(y2 - y1);		 // 0, -5 = 5
	int sx = (x1 < x2) ? 1 : -1; // 1
	int sy = (y1 < y2) ? 1 : -1; // -1
	int err = dx - dy;			 // 0
	int err2;
	int r, g, b;
	float position;

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

		err2 = 2 * err; // 0
		if (err2 > -dy) // yes
		{
			err -= dy; // -5
			x1 += sx;  // x1 + 1 = 6
		}
		if (err2 < dx) // yes
		{
			err += dx; // -5 + 5 = 0
			y1 += sy;  // y1 -1 = 4
		}
	}
}

void draw_circle(t_img *img, t_map *map)
{
	int x;
	int y;
	float xx = 0;
	float yy = 0;
	

	float	off_x = map->num_rows / 2;
	float	off_y = map->num_cols / 2;

	x = 0;
	while (x < map->num_rows)
	{
		y = 0;
		while (y < map->num_cols)
		{
			int z = map->coords[x][y].value * map->descale_z;

			int r = sqrt((x - off_x) * (x - off_x) + (y - off_y) * (y - off_y)); //-2 -2  -2 -1  -2 0  -2 1  -2 2 
			// r = r * 40 + z * 2;

			printf("z: %d, r: %d\n", z, r);
			//int r2 = 1 * 20;

			// int r3 = sqrt(y * y + x * x ) * 20;
			// printf("r3: %d\n", r3);

			float theta = atan2(y - off_y, x - off_x);
			//printf("theta: %f\n", theta);

			// float theta_degrees = theta * (180.0 / M_PI);
			// printf("theta: %f\n\n", theta_degrees);
        		
			xx = r * cos(2 * M_PI * (theta));
            yy = r * sin(2 * M_PI * (theta));
			//printf("x: %d, y: %d, xx: %f, yy: %f\n", x, y, xx, yy);
			
			//z = r * cos(M_PI * (theta));

			xx = xx * cos(map->a_z) - yy * sin(map->a_z);
			yy = (xx * sin(map->a_z) + yy * cos(map->a_z)) * cos(map->a_x) * sin(map->a_x);

 			xx = xx * map->scale + map->move_x;
			yy = yy * map->scale + map->move_y;

			img_pix_put(img, xx + WIDTH / 2, yy + HEIGHT / 2, PURPLE_PIXEL);

			// xx = r3 * cos(2 * M_PI * (theta));
            // yy = r3 * sin(2 * M_PI * (theta));
			// img_pix_put(img, xx + WIDTH / 2, yy + HEIGHT / 2, PURPLE_PIXEL);
			y++;
		}
		x++;
	}
}

void draw_lines(t_img *img, t_map *map)
{
	int x;
	int y;
	float nx_next;
	float ny_next;
	float nx;
	float ny;

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
			}
			if (y < map->num_cols - 1)
			{
				nx_next = map->coords[x][y + 1].x_iso + WIDTH / 2;
				ny_next = map->coords[x][y + 1].y_iso + HEIGHT / 2;
				t_color color_next = map->coords[x][y + 1].color;
				draw_l(img, nx, ny, nx_next, ny_next, color, color_next);
			}
			y++;
		}
		x++;
	}
}