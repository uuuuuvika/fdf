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

int draw_dots(t_img *img, t_iso output_iso[4], int size)
{
	int i = 0;
	int offset = 40;
	while (i < size)
	{
		img_pix_put(img, output_iso[i].iso_x + offset*(i+1), output_iso[i].iso_y + offset*(i+1), GREEN_PIXEL);
		i++;
	}
	return (0);
}

// not a real iso coordinates, but a simplified ones
t_iso cartesian_to_iso(double x, double y, double z)
{
	t_iso iso_coordinates;
	iso_coordinates.iso_x = (x - y);
	iso_coordinates.iso_y = (x + y) / 2 - z;

	return iso_coordinates;
}

void convert_array_to_iso(t_cart input_cartes[], t_iso output_iso[], int size) {
    for (int i = 0; i < size; i++) {
        output_iso[i] = cartesian_to_iso(input_cartes[i].x, input_cartes[i].y, input_cartes[i].z);
    }
}

int render(t_data *data)
{
	if (data->win_ptr == NULL)
		return (1);
	//draw_square(&data->img);
	//t_cart input_cartesian[4] = {{50, 50, 0}, {50, 100, 0}, {100, 50, 0}, {100, 100, 0}};

	t_iso output_iso[4];
	t_cart input_cartes[4];

    input_cartes[0].x = 50.0;
    input_cartes[0].y = 50.0;
    input_cartes[0].z = 0.0;

    input_cartes[1].x = 50.0;
    input_cartes[1].y = 100.0;
    input_cartes[1].z = 6.0;

    input_cartes[2].x = 100.0;
    input_cartes[2].y = 50.0;
    input_cartes[2].z = 0.0;

    input_cartes[3].x = 100.0;
    input_cartes[3].y = 100.0;
    input_cartes[3].z = 0.0;

	convert_array_to_iso(input_cartes, output_iso, 4);

	draw_dots(&data->img, output_iso, 4);

	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
	return (0);
}


int main(void)
{
	// t_cart c_c = {2.00, 1.00, 0.00};
	// t_iso i_c = cartesian_to_iso(c_c.x, c_c.y, c_c.z);


	t_data data;

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

	// print_gradient(data.img.gradient);

	// printf("Cartesian Coordinates: %.lf, %.lf, %.lf\n",
	// 	   c_c.x, c_c.y, c_c.z);

	// printf("Isometric Coordinates: (%.2f, %.2f)\n",
	// 	   i_c.iso_x, i_c.iso_y);

	mlx_loop_hook(data.mlx_ptr, &render, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
	mlx_loop(data.mlx_ptr);

	free(gradient);
	return (0);
}
