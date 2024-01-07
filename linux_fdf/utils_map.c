#include "fdf.h"

// get number of rows in map
// get number of columns in map
// bring back error checking for bad num columns
void read_map(int fd, t_map *map)
{
	int num_rows;
	int num_cols;
	char *line;
	char **cols;

	num_rows = 0;
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
	// map->a_z = 0.00;
	// map->a_x = 0.00;
	malloc_for_z(map);
	close(fd);
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

void free_arr2D(char **arr2D)
{
	int i;

	i = 0;
	while (arr2D[i] != NULL && arr2D[i][0] != '\n')
		free(arr2D[i++]);
	free(arr2D);
}

void cartesian_to_iso(t_map *map)
{
	int x;
	int y;
	int z;
	double scale;

	scale = 20.0;
	x = 0;

	int off_x = map->num_rows / 2;
	int off_y = map->num_cols / 2;
	
	while (x < map->num_rows)
	{
		y = 0;
		while (y < map->num_cols)
		{
			z = map->coords[x][y].value;

			//printf("off_x: %f, off_y: %f\n", off_x, off_y);
			float cos_z = cos(map->a_z);
			float sin_z = sin(map->a_z);
			float cos_x = cos(map->a_x);
			float sin_x = sin(map->a_x);

			// map->coords[x][y].x_iso = x * cos(map->a_z) - y * sin(map->a_z);
			// map->coords[x][y].y_iso = (x * sin(map->a_z) + y * cos(map->a_z)) * cos(map->a_x) + z * sin(map->a_x);
			
			double xx;
			double yy;

			xx = (x - off_x) * cos_z - (y - off_y) * sin_z;
			yy = (x - off_x) * sin_z + (y - off_y) * cos_z;

			// rotate around x-axis:
			yy = yy * cos_x - z * sin_x;
			// z = yy * sin_x + z * cos_x;

			map->coords[x][y].x_iso = xx * scale;
			map->coords[x][y].y_iso = yy * scale;
			// printf("z=%d x_iso=%f y_iso=%f\n", z, map->coords[(int)x][(int)y].x_iso, map->coords[(int)x][(int)y].y_iso);
			y++;
		}
		x++;
	}

}