#include "fdf.h"

// get number of rows in map
// get number of columns in map
// bring back error checking for bad num columns
void read_map(int fd, t_map *map)
{
	int num_rows;
	int num_cols;
	int num_values;
	char *line;
	char **values;
	char **len;

	num_cols = 0;
	num_rows = 0;

	while ((line = get_next_line(fd)) != NULL)
	{
		num_rows++;
		len = ft_split(line, ' ');
		num_cols = 0;
		while (len[num_cols] != NULL && len[num_cols][0] != '\n')
			num_cols++;
		printf("num_cols: %d\n", num_cols);

		int j = 0;
		while (len[j] != NULL && len[j][0] != '\n')
			free(len[j++]);
		free(len);
		free(line);
	}
	map->max_num_cols = num_cols;
	map->num_rows = num_rows;
	map->a_z = 30.0 / 180 * 3.14159;
	map->a_x = 30.0 / 180 * 3.14159;
	map->values = malloc(sizeof(int *) * num_rows);
	int i = 0;
	while (i < num_rows)
	{
		map->values[i] = malloc(sizeof(int) * num_cols);
		i++;
	}

	// close(fd);

	fd = open("maps/elem.fdf", O_RDONLY);
	i = 0;
	while (i < num_rows)
	{
		line = get_next_line(fd);
		values = ft_split(line, ' ');

		num_values = 0;
		while (values[num_values] != NULL && values[num_values][0] != '\n')
		{
			map->values[i][num_values] = ft_atoi(values[num_values]);
			num_values++;
		}
		i++;
	}
	close(fd);
}