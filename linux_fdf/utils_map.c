#include "fdf.h"

int read_map(int fd, t_map *map)
{
	int num_rows;
	int num_cols;
	char *line;
	char **cols;

	num_rows = 0;
	if (fd < 0)
		return (1);
	while ((line = get_next_line(fd)) != NULL)
	{
		num_rows++;
		cols = ft_split(line, ' ');
		num_cols = 0;
		while (cols[num_cols] != NULL && cols[num_cols][0] != '\n')
			num_cols++;
		free_arr2D(cols);
		free(line);
	}
	map->num_cols = num_cols;
	map->num_rows = num_rows;
	map->a_z = -135.00 / 180 * 3.14159;
	map->a_x = -125.00 / 180 * 3.14159;
	map->scale = 25.0;
	map->rotation_active = false;
	map->translate_active = false;
	malloc_for_z(map);
	close(fd);
	return (0);
}

void malloc_for_z(t_map *map)
{
	int i;

	map->coords = malloc(sizeof(t_coords *) * map->num_rows);
	i = 0;
	while (i < map->num_rows)
	{
		map->coords[i] = malloc(sizeof(t_coords) * map->num_cols);
		i++;
	}
}

void fill_z(int fd, t_map *map)
{
	int i;
	char *line;
	char **values;
	int num_values;

	i = 0;
	while (i < map->num_rows)
	{
		line = get_next_line(fd);
		values = ft_split(line, ' ');
		num_values = 0;
		while (values[num_values] != NULL && values[num_values][0] != '\n')
		{
			map->coords[i][num_values].value = ft_atoi(values[num_values]);
			num_values++;
		}
		i++;
		free_arr2D(values);
		free(line);
	}
	close(fd);
}

void cartesian_to_iso(t_map *map)
{
	int x;
	int y;
	int z;
	double xx;
	double yy;
	int off_x = map->num_rows / 2;
	int off_y = map->num_cols / 2;

	x = 0;
	while (x < map->num_rows)
	{
		y = 0;
		while (y < map->num_cols)
		{
			z = map->coords[x][y].value;
			xx = (x - off_x) * cos(map->a_z) - (y - off_y) * sin(map->a_z);
			yy = (x - off_x) * sin(map->a_z) + (y - off_y) * cos(map->a_z);
			yy = yy * cos(map->a_x) - z * sin(map->a_x);

			// printf("xx: %f, yy: %f\n", xx, yy);
			// printf("scale: %f\n", map->scale);

			map->coords[x][y].x_iso = xx * map->scale;
			map->coords[x][y].y_iso = yy * map->scale;
			y++;
		}
		x++;
	}
}