#include "fdf.h"

int destroy_win_and_img(t_data *data) 
{
    if (data->img.mlx_img != NULL) {
        mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
        data->img.mlx_img = NULL;
    }
    if (data->win_ptr != NULL) {
        mlx_destroy_window(data->mlx_ptr, data->win_ptr);
        data->win_ptr = NULL;
        free(data->win_ptr);
    }
    if (data->mlx_ptr != NULL) {
        mlx_destroy_display(data->mlx_ptr);
        data->mlx_ptr = NULL;
        free(data->mlx_ptr);
    }
    exit(0);
}

void free_arr2D(char **arr2D)
{
	int i;

	i = 0;
	while (arr2D[i] != NULL && arr2D[i][0] != '\n')
		free(arr2D[i++]);
	free(arr2D);
}