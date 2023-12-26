#include "fdf.h"

#define KEY_ESC 53

int handle_keypress(int key, t_data *data)
{
	if (key == KEY_ESC)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
	}
	return (0);
}

int render(t_data *data)
{
	if (data->win_ptr != NULL)
	{
		for(int i = 0; i < HEIGHT; i++)
			for(int j = 0; j < WIDTH; j++)
				mlx_pixel_put(data->mlx_ptr, data->win_ptr,
							  j, i, GRN_PIXEL);
		for(int i = 0; i < HEIGHT; i++)
			mlx_pixel_put(data->mlx_ptr, data->win_ptr,
						  i, i, RED_PIXEL);
		for(int i = 0; i < WIDTH; i++)
			mlx_pixel_put(data->mlx_ptr, data->win_ptr,
						  i, HEIGHT / 2, RED_PIXEL);
		for(int i = 0; i < HEIGHT; i++)
			mlx_pixel_put(data->mlx_ptr, data->win_ptr,
						  WIDTH / 2, i, RED_PIXEL);
		// mlx_pixel_put(data->mlx_ptr, data->win_ptr,
		// 			  WIDTH / 2, HEIGHT / 2, RED_PIXEL);
	}

	return (0);
}

int main(void)
{
	t_data data;

	data.mlx_ptr = mlx_init();

	if (data.mlx_ptr == NULL)
		return (MLX_ERROR);

	data.win_ptr = mlx_new_window(data.mlx_ptr, WIDTH, HEIGHT, "fdf");

	if (data.win_ptr == NULL)
	{
		free(data.win_ptr);
		return (MLX_ERROR);
	}

	mlx_loop_hook(data.mlx_ptr, &render, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);

	mlx_loop(data.mlx_ptr);
	free(data.mlx_ptr);
}