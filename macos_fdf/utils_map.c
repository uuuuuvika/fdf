#include "fdf.h"

int read_map(int fd, t_map *map)
{
	int num_rows;
	int num_cols;
	char *line;
	char **cols;
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
	map->a_z = -135.00 / 180 * 3.14159;
	map->a_x = -125.00 / 180 * 3.14159;
	map->scale = 25.0;
	map->descale_z = 1.0;
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
			char **all_pack = ft_split(values[num_values], ',');
			// if (all_pack[1] != NULL)
			// {
			// 	map->has_color = true;
			// 	map->coords[i][num_values].color = hex_to_color(all_pack[1]);
			// }
			map->coords[i][num_values].value = ft_atoi(all_pack[0]);
			free_arr2D(all_pack);
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
			z = map->coords[x][y].value * map->descale_z;
			xx = (x - off_x) * cos(map->a_z) - (y - off_y) * sin(map->a_z);
			yy = ((x - off_x) * sin(map->a_z) + (y - off_y) * cos(map->a_z)) * cos(map->a_x) - z * sin(map->a_x);
			//yy = yy * cos(map->a_x) - z * sin(map->a_x);
			map->coords[x][y].r = sqrt(xx * xx + yy * yy + z * z);
			map->coords[x][y].x_iso = xx * map->scale + map->move_x;
			map->coords[x][y].y_iso = yy * map->scale + map->move_y;
			y++;
		}
		x++;
	}
}

void cartesian_to_spherical(t_map *map)
{
	t_spherical result;
	int x;
	int y;
	int z;

	x = 0;
	while (x < map->num_rows)
	{
		y = 0;
		while (y < map->num_cols)
		{
			z = map->coords[x][y].value * map->descale_z;
			int xx = x * map->scale;
			int yy = y * map->scale;
			int zz = z * map->scale;
			//polar coordinates of x and y
			result.r = sqrt(xx * xx + yy * y + zz * zz);
			result.theta = atan2(yy, xx) * 180 / 3.14159;
			result.phi = atan2(sqrt(xx * xx + yy * yy), zz) * 180 / 3.14159;				
			printf
			(
				"x: %i, y: %i, r: %f, theta: %f\n",
				x,
				y,
				result.r,
				result.theta
			);

			map->coords[x][y].r = result.r;
			map->coords[x][y].theta = result.theta;
			map->coords[x][y].phi = result.phi;
			y++;
		}
		x++;
	}
}

void create_map(char *argv, t_data *data, t_color *gradient)
{
	char *map_name;

	map_name = ft_strjoin("maps/", argv);
	map_name = ft_spec_strjoin(map_name, ".fdf");
	if (read_map(open(map_name, O_RDONLY), &data->map) != 0)
	{
		free(map_name);
		free(gradient);
		printf("WRONG MAP! :(\n");
		destroy_win_and_img(data);
	}
	fill_z(open(map_name, O_RDONLY), &data->map);
	if (data->map.has_color == false)
		colorize_points(&data->map);
	free(map_name);
}