#include "fdf.h"

int	init_map(t_map *map, t_color *gradient)
{
	map->num_rows = 0;
	map->num_cols = 0;
	map->coords = NULL;
	map->move_x = 0;
	map->move_y = 0;
	map->min_val = 0;
	map->max_val = 0;
	map->a_z = -135.00 / 180 * M_PI;
	map->a_x = -125.00 / 180 * M_PI;
	map->scale = 20.0;
	map->descale_z = 1.0;
	map->rotation_active = false;
	map->translate_active = false;
	map->gradient = gradient;
	return (0);
}

int	read_map(int fd, t_map *map)
{
	char	*line;
	char	**cols;

	if (fd < 0)
		return (1);
	line = get_next_line(fd);
	while (line != NULL)
	{
		map->num_rows++;
		cols = ft_split(line, ' ');
		if (map->num_rows == 1)
			map->num_cols = count_columns(cols);
		else
		{
			if (count_columns(cols) != map->num_cols)
			{
				free_temp_arrays(cols, line);
				return (1);
			}
		}
		free_temp_arrays(cols, line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}

int	count_columns(char **cols)
{
	int	count;

	count = 0;
	while (cols[count] != NULL && cols[count][0] != '\n')
		count++;
	return (count);
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
		free_temp_arrays(values, line);
	}
	close(fd);
}

void	create_map(char *argv, t_data *data, t_color *gradient)
{
	char	*map_name;

	map_name = ft_strjoin("maps/", argv);
	map_name = ft_spec_strjoin(map_name, ".fdf");
	init_map(&data->map, gradient);
	if (read_map(open(map_name, O_RDONLY), &data->map) != 0)
	{
		free(map_name);
		printf("WRONG MAP! :(\n");
		destroy_win_and_img(data);
	}
	malloc_for_z(&data->map);
	fill_z(open(map_name, O_RDONLY), &data->map);
	find_extremes(&data->map);
	if (abs(data->map.min_val - data->map.max_val) > 40)
		data->map.descale_z = 0.1;
	colorize_points(&data->map);
	free(map_name);
}
