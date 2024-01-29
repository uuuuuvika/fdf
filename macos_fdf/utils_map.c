#include "fdf.h"

int	init_map(t_map *map, t_color *gradient) //do i need them all?
{
	map->num_rows = 0;
	map->num_cols = 0;
	map->coords = NULL;
	map->move_x = 0;
	map->move_y = 0;
	map->min_val = 0;
	map->max_val = 0;
	map->a_z = -135.00 / 180 * 3.14159;
	map->a_x = -125.00 / 180 * 3.14159;
	map->scale = 20.0;
	map->descale_z = 1.0;
	map->rotation_active = false;
	map->translate_active = false;
	map->gradient = gradient;
	return (0);
}

int	read_map(int fd, t_map *map)
{
	int		num_rows;
	int		num_cols;
	char	*line;
	char	**cols;

	if (fd < 0)
		return (1);
	num_rows = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		num_rows++;
		cols = ft_split(line, ' ');
		num_cols = 0;
		while (cols[num_cols] != NULL && cols[num_cols][0] != '\n')
			num_cols++;
		free_arr2D(cols);
		free(line);
		line = get_next_line(fd);
	}
	map->num_cols = num_cols;
	map->num_rows = num_rows;
	malloc_for_z(map);
	close(fd);
	return (0);
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
	fill_z(open(map_name, O_RDONLY), &data->map);
	find_extremes(&data->map);
	if (abs(data->map.min_val - data->map.max_val) > 40)
		data->map.descale_z = 0.1;
	colorize_points(&data->map);
	free(map_name);
}
