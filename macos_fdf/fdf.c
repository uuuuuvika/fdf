#include "fdf.h"

static double last_a_z = 0.0;
static double last_a_x = 0.0;

double get_position(int x1, int x2, int y1, int y2, int x_cur, int y_cur)
{
	double full_dist = hypot(x2 - x1, y2 - y1);
	// the distance between beg. and the current point
	double dist_to_current = hypot(x_cur - x1, y_cur - y1);
	if (full_dist != 0.0)
		// relative position of a point (x_cur, y_cur)
		// along a line between (x1, y1) and (x2, y2)
		return (dist_to_current / full_dist);
	return 1.0;
}

void draw_line(t_img *img, int x1, int y1, int x2, int y2)
{
	int x1_start = x1;
	int y1_start = y1;

	int dx = abs(x2 - x1);
	int dy = abs(y2 - y1);
	int sx = (x1 < x2) ? 1 : -1;
	int sy = (y1 < y2) ? 1 : -1;
	int err = dx - dy;
	int err2;

	while (!(x1 == x2 && y1 == y2))
	{
		if (x1 >= 0 && x1 <= WIDTH && y1 >= 0 && y1 <= HEIGHT)
		{
			double position = get_position(x1_start, x2, y1_start, y2, x1, y1);
			//printf("position: %f\n", position);
			// the gradient will be drawn from the first color to the second color
			// the first color is the color of the leftmost pixel in the line
			// the second color is the color of the rightmost pixel in the line
			// the color of the current pixel is calculated by interpolating between the two colors
			int r = round(img->gradient[0].r * (1 - position) + img->gradient[1].r * position);
			int g = round(img->gradient[0].g * (1 - position) + img->gradient[1].g * position);
			int b = round(img->gradient[0].b * (1 - position) + img->gradient[1].b * position);
			int color = (r << 16) | (g << 8) | b;
			img_pix_put(img, x1, y1, color);
		}

		err2 = 2 * err;
		if (err2 > -dy)
		{
			err -= dy;
			x1 += sx;
		}
		if (err2 < dx)
		{
			err += dx;
			y1 += sy;
		}
	}
}

// void draw_line(t_img *img, int x1, int y1, int x2, int y2)
// {
// 	int dx = abs(x2 - x1);
// 	int dy = abs(y2 - y1);
// 	int sx = (x1 < x2) ? 1 : -1;
// 	int sy = (y1 < y2) ? 1 : -1;
// 	int err = dx - dy;
// 	int err2;

// 	while (!(x1 == x2 && y1 == y2))
// 	{
// 		if (1 >= 0 && x1 <= WIDTH && y1 >= 0 && y1 <= HEIGHT)
// 			img_pix_put(img, x1, y1, GREEN_PIXEL);
// 		err2 = 2 * err;
// 		if (err2 > -dy)
// 		{
// 			err -= dy;
// 			x1 += sx;
// 		}
// 		if (err2 < dx)
// 		{
// 			err += dx;
// 			y1 += sy;
// 		}
// 	}
// }

void draw_lines(t_img *img, t_map *map)
{
	int x;
	int y;
	double nx_next;
	double ny_next;
	double nx;
	double ny;

	x = 0;
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
	double xx, yy;
	int x, y;

	x = 0;
	while (x < map->num_rows)
	{
		y = 0;
		while (y < map->num_cols)
		{
			// z = map->coords[(int)x][(int)y].value;
			xx = map->coords[x][y].x_iso + WIDTH / 2;
			yy = map->coords[x][y].y_iso + HEIGHT / 2;

			if (xx >= 0 && xx <= WIDTH && yy >= 0 && yy <= HEIGHT)
				img_pix_put(img, xx, yy, PURPLE_PIXEL);
			y++;
		}
		x++;
	}
}

int render(t_data *data)
{
	if (data->win_ptr == NULL)
		return (MLX_ERROR);
	if (last_a_z != data->map.a_z || last_a_x != data->map.a_x)
	{
		mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
		data->img.mlx_img = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
		data->img.addr = mlx_get_data_addr(data->img.mlx_img, &data->img.bpp, &data->img.line_len, &data->img.endian);
		cartesian_to_iso(&data->map);
		draw_lines(&data->img, &data->map);
		 //draw_dots(&data->img, &data->map);
		last_a_z = data->map.a_z;
		last_a_x = data->map.a_x;
		printf("a_z: %f, a_x: %f\n", data->map.a_z, data->map.a_x);
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
	}
	return (0);
}

int main(void)
{
	static t_data data; //???
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

	// TODO: make a string name(fd)into constant
	read_map(open("maps/42.fdf", O_RDONLY), &data.map);
	fill_z(open("maps/42.fdf", O_RDONLY), &data.map);
	cartesian_to_iso(&data.map);

	draw_lines(&data.img, &data.map);
	// draw_dots(&data.img, &data.map);

	print_gradient(data.img.gradient);

	mlx_loop_hook(data.mlx_ptr, &render, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);

	mlx_loop(data.mlx_ptr);

	mlx_destroy_image(data.mlx_ptr, data.img.mlx_img);
	mlx_destroy_window(data.mlx_ptr, data.win_ptr);
	data.win_ptr = NULL;
	free(data.win_ptr);
	free(gradient);
	return (0);
}
