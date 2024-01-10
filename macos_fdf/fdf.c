#include "fdf.h"
#include <CoreGraphics/CoreGraphics.h>

static double last_a_z = 0.0;
static double last_a_x = 0.0;

void getMousePosition(int *x, int *y)
{
	CGEventRef event = CGEventCreate(NULL);
	CGPoint mouseLoc = CGEventGetLocation(event);
	*x = (int)mouseLoc.x;
	*y = (int)mouseLoc.y;
	printf("Mouse location: %f %f\n", mouseLoc.x, mouseLoc.y);
	CFRelease(event);
}

double get_position(int x1, int x2, int y1, int y2, int x_cur, int y_cur)
{
	double full_dist = hypot(x2 - x1, y2 - y1);
	double dist_to_current = hypot(x_cur - x1, y_cur - y1);
	if (full_dist != 0.0)
		return (dist_to_current / full_dist);
	return 1.0;
}

void draw_base_line(t_img *img, int x1, int y1, int x2, int y2)
{
	int dx = abs(x2 - x1);
	int dy = abs(y2 - y1);
	int sx = (x1 < x2) ? 1 : -1;
	int sy = (y1 < y2) ? 1 : -1;
	int err = dx - dy;
	int err2;

	while (!(x1 == x2 && y1 == y2))
	{
		if (1 >= 0 && x1 <= WIDTH && y1 >= 0 && y1 <= HEIGHT)
			img_pix_put(img, x1, y1, gradient_to_int(&img->gradient[1]));
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

void draw_far_line(t_img *img, int x1, int y1, int x2, int y2)
{
	int dx = abs(x2 - x1);
	int dy = abs(y2 - y1);
	int sx = (x1 < x2) ? 1 : -1;
	int sy = (y1 < y2) ? 1 : -1;
	int err = dx - dy;
	int err2;

	while (!(x1 == x2 && y1 == y2))
	{
		if (1 >= 0 && x1 <= WIDTH && y1 >= 0 && y1 <= HEIGHT)
			img_pix_put(img, x1, y1, gradient_to_int(&img->gradient[0]));
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

void draw_lines(t_img *img, t_map *map)
{
	int x;
	int y;
	double nx_next;
	double ny_next;
	double nz_next;
	double nx;
	double ny;
	int nz;

	x = 0;
	while (x < map->num_rows)
	{
		y = 0;
		while (y < map->num_cols)
		{
			nx = map->coords[x][y].x_iso + WIDTH / 2;
			ny = map->coords[x][y].y_iso + HEIGHT / 2;
			nz = map->coords[x][y].value;

			if (x < map->num_rows - 1)
			{
				nx_next = map->coords[x + 1][y].x_iso + WIDTH / 2;
				ny_next = map->coords[x + 1][y].y_iso + HEIGHT / 2;
				nz_next = map->coords[x + 1][y].value;
				if (nz == nz_next && nz == 0)
					draw_base_line(img, nx, ny, nx_next, ny_next);
				else if (nz == nz_next)
					draw_far_line(img, nx, ny, nx_next, ny_next);
				else
					draw_line(img, nx, ny, nx_next, ny_next);
			}
			if (y < map->num_cols - 1)
			{
				nx_next = map->coords[x][y + 1].x_iso + WIDTH / 2;
				ny_next = map->coords[x][y + 1].y_iso + HEIGHT / 2;
				nz_next = map->coords[x][y + 1].value;
				if (nz == nz_next && nz == 0)
					draw_base_line(img, nx, ny, nx_next, ny_next);
				else if (nz == nz_next)
					draw_far_line(img, nx, ny, nx_next, ny_next);
				else
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

void update_angle(double* angle, int old_position, int new_position, float increment) {
    if (new_position > old_position)
        *angle -= increment;
    else if (new_position < old_position)
        *angle += increment;
}

int render(t_data *data)
{
	if (data->win_ptr == NULL)
		return (MLX_ERROR);

	static int mouse_x;
	static int mouse_y;

	getMousePosition(&mouse_x, &mouse_y);

	update_angle(&data->map.a_z, data->mouse_x, mouse_x, 0.05);
	update_angle(&data->map.a_x, data->mouse_y, mouse_y, 0.05);

	data->mouse_x = mouse_x;
	data->mouse_y = mouse_y;

	if (last_a_z != data->map.a_z || last_a_x != data->map.a_x)
	{
		mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
		data->img.mlx_img = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
		data->img.addr = mlx_get_data_addr(data->img.mlx_img, &data->img.bpp, &data->img.line_len, &data->img.endian);
		// printf("adress: %p\n", data->img.addr);
		cartesian_to_iso(&data->map);
		draw_lines(&data->img, &data->map);
		// draw_dots(&data->img, &data->map);
		last_a_z = data->map.a_z;
		last_a_x = data->map.a_x;
		// printf("a_z: %f, a_x: %f, a_y: %f\n", data->map.a_z * 180 / 3.14159, data->map.a_x * 180 / 3.14159, data->map.a_y * 180 / 3.14159);
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
	}
	return (0);
}

int main(int argc, char **argv)
{
	static t_data data; //???
	t_color *gradient = gen_gradient();
	char *map_name;

	if (argc != 2)
	{
		printf("WRONG MAP OR NO MAP :(\n");
		return (MLX_ERROR);
	}
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

	map_name = ft_strjoin("maps/", argv[1]);
	map_name = ft_spec_strjoin(map_name, ".fdf");

	// int mouseX, mouseY;
	getMousePosition(&data.mouse_x, &data.mouse_y);
	read_map(open(map_name, O_RDONLY), &data.map);
	fill_z(open(map_name, O_RDONLY), &data.map);

	free(map_name);

	cartesian_to_iso(&data.map);

	draw_lines(&data.img, &data.map);
	// draw_dots(&data.img, &data.map);

	print_gradient(data.img.gradient);

	mlx_loop_hook(data.mlx_ptr, &render, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);

	mlx_loop(data.mlx_ptr);

	mlx_destroy_image(data.mlx_ptr, data.img.mlx_img);
	mlx_destroy_window(data.mlx_ptr, data.win_ptr);
	// mlx_destroy_display(data.mlx_ptr);
	data.win_ptr = NULL;
	free(data.win_ptr);
	free(gradient);
	return (0);
}
