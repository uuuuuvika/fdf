#include "fdf.h"

void draw_dots(t_img *img, t_map *map)
{
	float xx, yy;
	int x, y;

	x = 0;

	while (x < map->num_rows)
	{
		y = 0;
		while (y < map->num_cols)
		{
			// z = map->coords[(int)x][(int)y].value;
			xx = map->coords[x][y].x_iso + WIDTH / 2;
			yy = map->coords[x][y].y_iso + HEIGHT / 2;

			if (xx >= 0 && xx <= WIDTH && yy >= 0 && yy <= HEIGHT)
				img_pix_put(img, xx, yy, PURPLE_PIXEL);
			y++;
		}
		x++;
	}
}

//animation base (looks good with t1)
// void cartesian_to_spherical(t_map *map)
// {
// 	// t_spherical result;
// 	int x;
// 	int y;
// 	// int z;
// 	// int off_x = map->num_rows / 2;
// 	// int off_y = map->num_cols / 2;

// 	x = 0;
// 	while (x < map->num_rows)
// 	{
// 		y = 0;
// 		while (y < map->num_cols)
// 		{
// 			int z = map->coords[x][y].value * map->descale_z;

// 			float xx = (sin(3.14159 * x / map->num_rows) + z * 0.001) * cos(2 * 3.14159 * y / map->num_cols);
// 			float yy = (sin(3.14159 * x / map->num_rows) - z * 0.001) * sin(2 * 3.14159 * y / map->num_cols);

// 			// float zz = cos(3.14159 * x * z / map->num_rows);
// 			// float zzz = cos(3.14159 * y * z / map->num_cols);
// 			float zz = cos(3.14159 * x / map->num_rows);

// 			// xx = (xx) * cos(map->a_z) - (yy) * sin(map->a_z);
// 			//  yy = ((xx) * sin(map->a_z) + (yy) * cos(map->a_z)) * cos(map->a_x) - zz * sin(map->a_x);

// 			yy = yy * cos(map->a_x) - zz * sin(map->a_x);

// 			map->coords[x][y].x_iso = (xx * map->scale + map->move_x);
// 			map->coords[x][y].y_iso = (yy * map->scale + map->move_y);
// 			y++;
// 		}
// 		x++;
// 	}
// }