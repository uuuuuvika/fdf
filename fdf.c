#include "fdf.h"

int draw_square(t_img *img)
{
	int side_length = 300;
	int x = WIDTH / 2 - side_length / 2;
	int y = HEIGHT / 2 - side_length / 2;

	for (int i = x; i < x + side_length; i++)
	{
		for (int j = y; j < y + side_length; j++)
		{
			int red = 0;
			int green = (i - x) * 255 / side_length;
			int blue = (j - y) * 255 / side_length;

			int color = (red << 16) | (green << 8) | blue;
			img_pix_put(img, i, j, color);
		}
	}
	return (0);
}

int render(t_data *data)
{
	if (data->win_ptr == NULL)
		return (1);
	draw_square(&data->img);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
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

	// gen_gradient();
	data.img.mlx_img = mlx_new_image(data.mlx_ptr, WIDTH, HEIGHT);
	data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp, &data.img.line_len, &data.img.endian);

	mlx_loop_hook(data.mlx_ptr, &render, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
	mlx_loop(data.mlx_ptr);

	return (0);
}
