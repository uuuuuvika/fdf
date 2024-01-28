#include "fdf.h"

int	init_map(t_map *map, t_color *gradient)
{
	map->num_rows = 0;
	map->num_cols = 0;
	map->coords = NULL;
	map->move_x = 0;
	map->move_y = 0;
	// map->a_z = 0;
	// map->a_x = 0;
	map->a_z = -135.00 / 180 * 3.14159;
	map->a_x = -125.00 / 180 * 3.14159;
	map->scale = 10.0; 
	map->descale_z = 1.0;
	map->rotation_active = false;
	map->translate_active = false;
	map->gradient = gradient;
	// map->has_color = false;
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
	malloc_for_z(map);
	close(fd);
	return (0);
}

void	malloc_for_z(t_map *map) //here are reachable bytes
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

void	fill_z(int fd, t_map *map)
{
	int		i;
	char	*line;
	char	**values;
	int		num_values;
	//char	**val_w_colors; 

	i = 0;
	while (i < map->num_rows)
	{
		line = get_next_line(fd);
		values = ft_split(line, ' ');
		num_values = 0;
		while (values[num_values] != NULL && values[num_values][0] != '\n')
		{
			//val_w_colors = ft_split(values[num_values], ',');
			// if (val_w_colors[1] != NULL)
			// {
			// 	map->has_color = true;
			// 	map->coords[i][num_values].color = hex_to_color(val_w_colors[1]);
			// }
			map->coords[i][num_values].value = ft_atoi(values[num_values]);
			//free_arr2D(val_w_colors);
			num_values++;
		}
		i++;
		free_arr2D(values);
		free(line);
	}
	close(fd);
}

void create_map(char *argv, t_data *data, t_color *gradient)
{
	char *map_name;

	map_name = ft_strjoin("maps/", argv);
	map_name = ft_spec_strjoin(map_name, ".fdf");
	init_map(&data->map, gradient);
	if (read_map(open(map_name, O_RDONLY), &data->map) != 0)
	{
		free(map_name);
		//free(gradient);
		//free(&data->map);
		printf("WRONG MAP! :(\n");
		destroy_win_and_img(data);
	}
	fill_z(open(map_name, O_RDONLY), &data->map);
	// if (data->map.has_color == false)
	colorize_points(&data->map);
	free(map_name);
}