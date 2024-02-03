#include "fdf.h"

void	rotate_over_z(float x, float y, float *xx, float *yy, float angle)
{
	*xx = x * cos(angle) - y * sin(angle);
	*yy = x * sin(angle) + y * cos(angle);
}

void	rotate_over_x(float y, float z, float *yy, float angle)
{
	*yy = y * cos(angle) + z * sin(angle);
}

int	xwo(t_map *map, int x)
{
	return (x - map->num_rows / 2);
}

int	ywo(t_map *map, int y)
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
			map->coords[x][y].x_iso = xx  * map->scale + map->move_x;
			map->coords[x][y].y_iso = yy  * map->scale + map->move_y;
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
	int relief;

	x = 0;
	while (x < map->num_rows)
	{
		y = 0;
		while (y < map->num_cols)
		{
			relief = map->coords[x][y].value * map->descale_z;
			xx = sin(M_PI * x / map->num_rows) * cos(2 * M_PI * y / map->num_cols) * (1 + relief / 6000.0);
			yy = sin(M_PI * x / map->num_rows) * sin(2 * M_PI * y / map->num_cols) * (1 + relief / 6000.0);
			zz = cos(M_PI * x / map->num_rows) * (1 + relief / 6000.0);
			rotate_over_z(xx, yy, &xx, &yy, map->a_z);
			rotate_over_x(yy, zz, &yy, map->a_x);
			map->coords[x][y].x_iso = xx * map->scale * 10 + map->move_x;
			map->coords[x][y].y_iso = yy * map->scale * 10 + map->move_y;
			y++;
		}
		x++;
	}
}

