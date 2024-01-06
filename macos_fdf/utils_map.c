#include "fdf.h"

void read_map(int fd, t_map *map)
{
	int		num_rows;
	int		num_cols;
	char	*line;
	char	**cols;

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
	map->a_z = 30.0 / 180 * 3.14159;
	map->a_x = 45.0 / 180 * 3.14159;
	malloc_for_z(map);
	close(fd);
}

void	malloc_for_z(t_map *map)
{
	int	i;

	map->coords = malloc(sizeof(t_coords *) * map->num_rows);
	i = 0;
	while (i < map->num_rows)
	{
		map->coords[i] = malloc(sizeof(t_coords) * map->num_cols);
		i++;
	}
}

void	fill_z(int fd, t_map *map)
{
	int		i;
	char	*line;
	char	**values;
	int		num_values;

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

	scale = 20.00;
	x = 0;
	while (x < map->num_rows)
	{
		y = 0;
		while (y < map->num_cols)
		{
			z = map->coords[x][y].value;
			map->coords[x][y].x_iso = x * cos(map->a_z) - y * sin(map->a_z);
			map->coords[x][y].y_iso = (x * sin(map->a_z) + y * cos(map->a_z)) * cos(map->a_x) - z * sin(map->a_x);

			map->coords[x][y].x_iso *= scale;
			map->coords[x][y].y_iso *= scale;
			// printf("z=%d x_iso=%f y_iso=%f\n", z, map->coords[(int)x][(int)y].x_iso, map->coords[(int)x][(int)y].y_iso);
			y++;
		}
		x++;
	}
}