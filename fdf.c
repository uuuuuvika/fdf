#include "fdf.h"

int draw_square(t_img *img)
{
	int side_length = 300;
	int x = WIDTH / 2 - side_length / 2;
	int y = HEIGHT / 2 - side_length / 2;

	int r_range = img->gradient[1].r - img->gradient[0].r;
	int g_range = img->gradient[1].g - img->gradient[0].g;
	int b_range = img->gradient[1].b - img->gradient[0].b;

	int initial_r = img->gradient[0].r;
	int initial_g = img->gradient[0].g;
	int initial_b = img->gradient[0].b;

	for (int i = x; i < x + side_length; i++)
	{
		for (int j = y; j < y + side_length; j++)
		{
			// // the number (0 to 255) will determine the intensity of the red,
			// // green and blue color components
			// int red = 0;
			// // (i - x) ---> horizontal position of the pixel within the square
			// int green = (i - x) * 50 / side_length;
			// // (j - y) ---> vertical position of the pixel within the square
			// int blue = (j - y) * 255 / side_length;

			// Interpolation is a mathematical technique used to estimate values that fall between known values.
			// (i - x): Represents the distance of the current pixel from the left edge of the square.
			// If the pixel is on the left edge, the distance is 0. If the pixel is on the right edge, the distance is side_length - 1.
			int red = initial_r + (i - x) * r_range / side_length;
			int green = initial_g + (i - x) * g_range / side_length;
			// Adds the interpolated value to the initial blue component of the first color in the gradient,
			// which is the blue component of the leftmost pixel in the square.
			// the same is done for the green and red component
			int blue = initial_b + (i - x) * b_range / side_length;

			int color = (red << 16) | (green << 8) | blue;
			img_pix_put(img, i, j, color);
		}
	}
	return (0);
}

int draw_dots(t_img *img, char **values, int rows, int columns)
{
	double x;
	double y;
	int z;
	double offset;
	double a;
	double scale;

	a = 30.0 / 180 * 3.14159;
	scale = 15;
	x = 0;
	double x45;
	double y45;
	offset = 300;

	while (x < rows)
	{
		y = 0;
		while (y < columns)
		{
			z = values[(int)x][(int)y];
			(void)z;

			// x45 = -(x*cos(a) - y *sin(a));
			// y45 = (x*sin(a) + y*cos(a));
			// y45 = (y45 * cos(a) - z * sin(a));
			// x45 = -(x * cos(a) - y * sin(a));
			// y45 = x * sin(a) + y * cos(a) * cos(a) - z * sin(a);
			x45 = x * cos(a) - y * cos(a);
			//y45 = x * sin(a) + y * cos(a) * cos(a) - 3.00 * sin(a);
			y45 = sin(a) * (x - y * sin(a) - 3.00) + y;

			x45 *= scale;
			y45 *= scale;

			// printf("x=%f, x45=%f, y=%f, y45=%f\n", x, x45, y, y45);
			img_pix_put(img, x45 + offset, y45 + offset, GREEN_PIXEL);
			y++;
		}
		x++;
	}
}

int render(t_data *data)
{
	if (data->win_ptr == NULL)
		return (1);
	// draw_square(&data->img);

	draw_dots(&data->img, data->img.map.values, data->img.map.num_rows, data->img.map.max_num_cols);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
	return (0);
}

int main(void)
{
	t_data data;
	int fd;

	t_color *gradient = gen_gradient();

	if (gradient == NULL)
		return (MLX_ERROR);

	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (MLX_ERROR);

	data.win_ptr = mlx_new_window(data.mlx_ptr, WIDTH, HEIGHT, "fdf");
	if (data.win_ptr == NULL)
	{
		free(data.win_ptr); // ???
		return (MLX_ERROR);
	}

	data.img.mlx_img = mlx_new_image(data.mlx_ptr, WIDTH, HEIGHT);
	data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp, &data.img.line_len, &data.img.endian);
	data.img.gradient = gradient;

	fd = open("maps/plat.fdf", O_RDONLY);

	read_map(fd, &data.img.map);
	close(fd);

	print_gradient(data.img.gradient);

	mlx_loop_hook(data.mlx_ptr, &render, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
	mlx_loop(data.mlx_ptr);

	free(gradient);
	return (0);
}
