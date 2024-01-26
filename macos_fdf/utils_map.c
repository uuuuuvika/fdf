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
	// map->a_z = -135.00 / 180 * 3.14159;
	// map->a_x = -125.00 / 180 * 3.14159;
	map->a_z = 0;
	map->a_x = 0;
	map->scale = 1.0;
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

void	cartesian_to_iso(t_map *map)
{
	int		x;
	int		y;
	int		z;
	float	xx;
	float	yy;
	int		off_x = map->num_rows / 2;
	int		off_y = map->num_cols / 2;

	x = 0;
	while (x < map->num_rows)
	{
		y = 0;
		while (y < map->num_cols)
		{
			z = map->coords[x][y].value * map->descale_z;
			xx = (x - off_x) * cos(map->a_z) - (y - off_y) * sin(map->a_z);
			yy = ((x - off_x) * sin(map->a_z) + (y - off_y) * cos(map->a_z)) * cos(map->a_x) - z * sin(map->a_x);
			// yy = yy * cos(map->a_x) - z * sin(map->a_x);
			//map->coords[x][y].r = sqrt(xx * xx + yy * yy + z * z);

			printf("x: %d, y: %d, xx: %f, yy: %f\n", x - off_x, y - off_y, xx, yy);

			map->coords[x][y].x_iso = xx * map->scale + map->move_x;
			map->coords[x][y].y_iso = yy * map->scale + map->move_y;
			y++;
		}
		x++;
	}
}

void cartesian_to_spherical(t_map *map)
{
	int x;
	int y;
	// int z;
	// int off_x = map->num_rows / 2;
	// int off_y = map->num_cols / 2;
	float xx = 0;
	float yy = 0;
	float zz = 0;

	int	off_x = map->num_rows / 2;
	int	off_y = map->num_cols / 2;

	x = 0;
	while (x < map->num_rows)
	{
		y = 0;
		while (y < map->num_cols)
		{
			//float r = sqrt(x * x + y * y + z * z);
			//int z = map->coords[x][y].value * map->descale_z;
		
			// rho must be positive
			// theta must be between 0 and 2pi
			// phi must be between 0 and pi

			// 	x = rho sin (phi) cos (theta)
			//	y = rho sin (phi) sin (theta)

			// z = rho cos (phi) 
			// r = rho sin (phi) 


			// circle with offset
			int z = map->coords[x][y].value * map->descale_z;
			int r = sqrt((x - off_x) * (x - off_x) + (y - off_y) * (y - off_y)); 
			printf("z: %d, r: %d\n", z, r);
			//int r2 = 1 * 20;

			double theta = atan2(y - off_y, x - off_x);
			//printf("theta: %f\n", theta);

			// double theta_degrees = theta * (180.0 / M_PI);
			// printf("theta: %f\n\n", theta_degrees);
        		
			xx = r * cos(2 * M_PI * theta);
            yy = r * sin(2 * M_PI * theta);

			
			// xx = sin(3.14159 * x / (map->num_rows)) * cos(2 * 3.14159 * y / (map->num_cols));
			// yy = sin(3.14159 * x / (map->num_rows)) * sin(2 * 3.14159 * y / (map->num_cols)); 
			// int theta = 2 * 3.14159 * y / (map->num_cols);
			
			//zz = cos(3.14159 * x / (map->num_rows));
			//double phi = atan(zz);
			zz = r * cos(M_PI * (theta));

			xx = xx * cos(map->a_z) - yy * sin(map->a_z);
			yy = (xx * sin(map->a_z) + yy * cos(map->a_z)) * cos(map->a_x) - z * sin(map->a_x);

			printf("x: %d, y: %d, xx: %f, yy: %f\n", x, y, xx, yy);

			map->coords[x][y].x_iso = xx * map->scale + map->move_x;
			map->coords[x][y].y_iso = yy * map->scale + map->move_y;
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