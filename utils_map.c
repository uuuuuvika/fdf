#include "fdf.h"

// get number of rows in map
// get number of columns in map
static size_t ft_spec_strlen(char *str)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char *ft_spec_strjoin(char *str1, char *str2)
{
	int i;
	char *newstr;

	i = 0;
	newstr = malloc(ft_spec_strlen(str1) + ft_spec_strlen(str2) + 1);
	if (!newstr)
		return (NULL);
	while (str1 && str1[i])
	{
		newstr[i] = str1[i];
		i++;
	}
	free(str1);
	while (*str2)
	{
		newstr[i++] = *str2;
		if (*str2++ == '\n')
			break;
	}
	newstr[i] = '\0';
	return (newstr);
}

void read_map(int fd, t_map *map)
{
	int num_rows;
	int max_num_cols;
	int num_values;
	char *line;
	char **values;
	char *all_values;

	max_num_cols = 0;
	num_rows = 0;
	all_values = NULL;
	// first find the longest line
	while ((line = get_next_line(fd)) != NULL)
	{
		num_rows++;
		int len = ft_strlen(line);

		if (len > max_num_cols)
			max_num_cols = len;
	}
	close(fd);
	// allocate memory for the map
	map->values = malloc(sizeof(int *) * num_rows);
	// then read the map
	fd = open("maps/plat.fdf", O_RDONLY);
	int i = 0;
	while (i < num_rows)
	{
		map->values[i] = malloc(sizeof(int) * max_num_cols);
		i++;
	}
	i = 0;
	while (i < num_rows)
	{
		line = get_next_line(fd);
		// TODO: add check if the line is == or < than max_num_cols

		values = ft_split(line, ' ');

		num_values = 0;
		while(values[num_values] != NULL && values[num_values][0] != '\n')
		{
			map->values[i][num_values] = ft_atoi(values[num_values]);
			num_values++;
		}
		i++;
	}
	// {
	// 	//num_rows++;
	// 	//int len = ft_strlen(line);

	// 	values = ft_split(line, ' ');
	// 	num_values = 0;
	// 	while (values[num_values] != NULL)
	// 	{
	// 		all_values = ft_spec_strjoin(all_values, values[num_values]);
	// 		num_values++;
	// 	}
	// 	if (num_rows == 1)
	// 		max_num_cols = num_values;

	// 	// else if (num_values != max_num_cols)
	// 	// {
	// 	// 	printf("YOU SUCK!");
	// 	// 	int i = 0;
	// 	// 	while (values[i] != NULL)
	// 	// 		free(values[i++]);
	// 	// 	free(values);
	// 	// 	exit(1);
	// 	// }
	// }
	int j = 0;
	while (values[j] != NULL)
		free(values[j++]);
	free(values);

	map->num_rows = num_rows;
	map->max_num_cols = max_num_cols;
	//map->values = ft_split(all_values, '\n');
	// for (int i = 0; map->values[i] != NULL; i++)
	// 	printf("Values: %s\n", map->values[i]);

}