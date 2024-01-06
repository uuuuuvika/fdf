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

void draw_line(t_img *img, double x1, double y1, double x2, double y2)
{
	// Iterators, counters required by algorithm
	double x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;
	// Calculate line deltas
	dx = x2 - x1;
	dy = y2 - y1;

	// Create a positive copy of deltas (makes iterating easier)
	dx1 = fabs(dx);
	dy1 = fabs(dy);
	// Calculate error intervals for both axis
	px = 2.00 * dy1 - dx1;
	py = 2.00 * dx1 - dy1;
	// The line is X-axis dominant
	if (dy1 <= dx1)
	{
		// Line is drawn left to right
		if (dx >= 0)
		{
			x = x1;
			y = y1;
			xe = x2;
		}
		else
		{ // Line is drawn right to left (swap ends)
			x = x2;
			y = y2;
			xe = x1;
		}
		if (x >= 0 && x <= WIDTH && y >= 0 && y <= HEIGHT)
			img_pix_put(img, x, y, GREEN_PIXEL);
		// Rasterize the line
		for (i = 0; x < xe; i++)
		{
			x = x + 1;
			// Deal with octants...
			if (px < 0)
			{
				px = px + 2.00 * dy1;
			}
			else
			{
				if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
				{
					y = y + 1.00;
				}
				else
				{
					y = y - 1;
				}
				px = px + 2 * (dy1 - dx1);
			}
			// Draw pixel from line span at
			// currently rasterized position
			if (x >= 0 && x <= WIDTH && y >= 0 && y <= HEIGHT)
				img_pix_put(img, x, y, GREEN_PIXEL);
		}
	}
	else
	{ // The line is Y-axis dominant
		// Line is drawn bottom to top
		if (dy >= 0)
		{
			x = x1;
			y = y1;
			ye = y2;
		}
		else
		{ // Line is drawn top to bottom
			x = x2;
			y = y2;
			ye = y1;
		}
		if (x >= 0 && x <= WIDTH && y >= 0 && y <= HEIGHT)
			img_pix_put(img, x, y, GREEN_PIXEL);
		// Rasterize the line
		for (i = 0; y < ye; i++)
		{
			y = y + 1;
			// Deal with octants...
			if (py <= 0)
			{
				py = py + 2 * dx1;
			}
			else
			{
				if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
				{
					x = x + 1;
				}
				else
				{
					x = x - 1;
				}
				py = py + 2 * (dx1 - dy1);
			}
			// Draw pixel from line span at
			// currently rasterized position
			if (x >= 0 && x <= WIDTH && y >= 0 && y <= HEIGHT)
				img_pix_put(img, x, y, GREEN_PIXEL);
			y++;
		}
	}
}

void draw_lines(t_img *img, t_map *map)
{
	int x;
	int y;
	double nx_next;
	double ny_next;
	double nx;
	double ny;

	// int scale;

	x = 0;
	// scale = 20;

	while (x < map->num_rows)
	{
		y = 0;
		while (y < map->num_cols)
		{
			nx = map->coords[x][y].x_iso + WIDTH / 2;
			ny = map->coords[x][y].y_iso + HEIGHT / 2;

			if (x < map->num_rows - 1)
			{
				nx_next = map->coords[x + 1][y].x_iso + WIDTH / 2;
				ny_next = map->coords[x + 1][y].y_iso + HEIGHT / 2;
				draw_line(img, nx, ny, nx_next, ny_next);
			}
			if (y < map->num_cols - 1)
			{
				nx_next = map->coords[x][y + 1].x_iso + WIDTH / 2;
				ny_next = map->coords[x][y + 1].y_iso + HEIGHT / 2;
				draw_line(img, nx, ny, nx_next, ny_next);
			}
			y++;
		}
		x++;
	}
}

void draw_dots(t_img *img, t_map *map)
{
	double x, y, xx, yy;

	x = 0;
	while (x < map->num_rows)
	{
		y = 0;
		while (y < map->num_cols)
		{
			// z = map->coords[(int)x][(int)y].value;
			xx = map->coords[(int)x][(int)y].x_iso + WIDTH / 2;
			yy = map->coords[(int)x][(int)y].y_iso + HEIGHT / 2;

			if (xx >= 0 && xx <= WIDTH && yy >= 0 && yy <= HEIGHT)
				img_pix_put(img, xx, yy, GREEN_PIXEL);
			y++;
		}
		x++;
	}
}

int render(t_data *data)
{
	if (data->win_ptr == NULL)
		return (MLX_ERROR);
	// draw_square(&data->img);

	static double last_a_z = 0;
	static double last_a_x = 0;
	if (last_a_z != data->map.a_z || last_a_x != data->map.a_x)
	{
		mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
		data->img.mlx_img = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
		cartesian_to_iso(&data->map);
		// draw_dots(&data->img, &data->map);
		draw_lines(&data->img, &data->map);
	}

	// draw_dots(&data->img, data->map.values, data->map.num_rows, data->map.num_cols, data->map.a_x, data->map.a_z);
	// loop(&data->img, &data->map);

	// draw_dots(&data->img, &data->map);

	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);

	last_a_z = data->map.a_z;
	last_a_x = data->map.a_x;

	return (0);
}

int main(void)
{
	static t_data data;
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

	// pylone has uneven columns ???
	read_map(open("maps/test.fdf", O_RDONLY), &data.map);
	fill_z(open("maps/test.fdf", O_RDONLY), &data.map);
	cartesian_to_iso(&data.map);
	// draw_dots(&data.img, &data.map);
	draw_lines(&data.img, &data.map);

	print_gradient(data.img.gradient);

	mlx_loop_hook(data.mlx_ptr, &render, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);

	mlx_loop(data.mlx_ptr);
	mlx_destroy_image(data.mlx_ptr, data.img.mlx_img);

	free(gradient);
	return (0);
}
