#include "fdf.h"

void rotate_over_z(int x, int y, float *xx, float *yy, float angle)
{
	*xx = x * cos(angle) - y * sin(angle);
	*yy = x * sin(angle) + y * cos(angle);
}

void rotate_over_x(float y, int z, float *yy, float angle)
{
	*yy = y * cos(angle) + z * sin(angle);
}

int xwo(t_map *map, int x)
{
    return (x - map->num_rows / 2);
}

int ywo(t_map *map, int y)
{
    return (y - map->num_cols / 2);
}

void cartesian_to_iso(t_map *map)
{
	int x;
	int y;
	int z;
	float xx;
	float yy;
   
	x = 0;
	while (x < map->num_rows)
	{
		y = 0;
		while (y < map->num_cols)
		{
			z = map->coords[x][y].value * map->descale_z;
			rotate_over_z(xwo(map, x), ywo(map, y), &xx, &yy, map->a_z);
			rotate_over_x(yy, z, &yy, map->a_x);
			map->coords[x][y].x_iso = xx  * map->scale+ map->move_x;
			map->coords[x][y].y_iso = yy  * map->scale+ map->move_y;
			y++;
		}
		x++;
	}
}

void cartesian_to_spherical(t_map *map)
{
	int x;
	int y;
	float xx = 0;
	float yy = 0;
	float zz = 0;

	x = 0;
	while (x < map->num_rows)
	{
		y = 0;
		while (y < map->num_cols)
		{
			int relief = map->coords[x][y].value * map->descale_z;
			// if (relief > 255)
			// 	relief = 255;

			float theta = M_PI * x / map->num_rows;	  // Latitude
			float phi = 2 * M_PI * y / map->num_cols; // Longitude

			xx = sin(theta) * cos(phi) * (1 + relief / 6000.0);
			yy = sin(theta) * sin(phi) * (1 + relief / 6000.0);
			zz = cos(theta) * (1 + relief / 6000.0);

			// rotation  around z axis
			float temp_x = xx * cos(map->a_z) - yy * sin(map->a_z);
			float temp_y = xx * sin(map->a_z) + yy * cos(map->a_z);
			// rotation around x axis
			yy = temp_y * cos(map->a_x) - zz * sin(map->a_x);

			map->coords[x][y].x_iso = temp_x * map->scale + map->move_x;
			map->coords[x][y].y_iso = yy * map->scale + map->move_y;
			y++;
		}
		x++;
	}
}
