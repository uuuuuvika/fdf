#include "fdf.h"
#include "../get_next_line/get_next_line.h"
#include "../lib/libft.h"

void read_map(char* file)
{
    FILE *file;
    int num_rows;
    int num_cols;
   // int **map;

    file = fopen(file, "r");
    if (file == NULL)
        exit(EXIT_FAILURE);

    


}