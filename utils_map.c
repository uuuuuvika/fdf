#include "fdf.h"

// get number of rows in map
// get number of columns in map
void read_map(int fd)
{
	int num_rows;
	int max_num_cols;
	int num_coordinates;
	char *line;
	char **only_coordinates;

	max_num_cols = 0;
	num_rows = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		num_rows++;

		only_coordinates = ft_split(line, ' ');

		num_coordinates = 0;
		while (only_coordinates[num_coordinates] != NULL)
			num_coordinates++;

		printf("Number of coordinates: %d\n", num_coordinates);
		
		if (num_coordinates > max_num_cols)
			max_num_cols = num_coordinates;
	}
	printf("Max number of columns: %d\n", max_num_cols);
	printf("Number of rows: %d\n", num_rows);

	// return (num_rows);
}