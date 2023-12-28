#include "fdf.h"

int draw_square(t_data *data)
{
	int side_length = 100;
	int x = WIDTH / 2 - side_length / 2;
	int y = HEIGHT / 2 - side_length / 2;

	if (data->win_ptr != NULL)
	{
		for (int i = x; i < x + side_length; i++)
		{
			for (int j = y; j < y + side_length; j++)
			{
				int red = 0;
				int green = (i - x) * 255 / side_length;
				int blue = (j - y) * 255 / side_length;
	
				int color = (red << 16) | (green << 8) | blue;

				mlx_pixel_put(data->mlx_ptr, data->win_ptr, i, j, color);
			}
		}
	}

	return (0);
}

int main(void)
{
	srand(time(NULL));

	t_data data;

	data.mlx_ptr = mlx_init();

	if (data.mlx_ptr == NULL)
		return (MLX_ERROR);

	data.win_ptr = mlx_new_window(data.mlx_ptr, WIDTH, HEIGHT, "Gradient Square");

	if (data.win_ptr == NULL)
	{
		free(data.win_ptr);
		return (MLX_ERROR);
	}

	//gen_gradient();

	mlx_loop_hook(data.mlx_ptr, &draw_square, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
	mlx_loop(data.mlx_ptr);

	return 0;
}
