#include "fdf.h"

void draw_line(t_img *img, int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;
	int err2;

    while (!(x1 == x2 && y1 == y2)) {
        if (1 >= 0 && x1 <= WIDTH && y1 >= 0 && y1 <= HEIGHT)
			img_pix_put(img, x1, y1, GREEN_PIXEL);
        err2 = 2 * err;
        if (err2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (err2 < dx) {
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
				draw_line(img, ceil(nx), ceil(ny), ceil(nx_next), ceil(ny_next));
			}
			if (y < map->num_cols - 1)
			{
				nx_next = map->coords[x][y + 1].x_iso + WIDTH / 2;
				ny_next = map->coords[x][y + 1].y_iso + HEIGHT / 2;
				draw_line(img, ceil(nx), ceil(ny), ceil(nx_next), ceil(ny_next));
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
	// draw_square(&data->img);

	static double last_a_z = 0;
	static double last_a_x = 0;
	if (last_a_z != data->map.a_z || last_a_x != data->map.a_x)
	{
		mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
		data->img.mlx_img = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
		last_a_z = data->map.a_z;
		last_a_x = data->map.a_x;
		cartesian_to_iso(&data->map);
		draw_lines(&data->img, &data->map);
		draw_dots(&data->img, &data->map);
		
	}
	//last_a_z = data->map.a_z;
	//last_a_x = data->map.a_x;
	//cartesian_to_iso(&data->map);
	// draw_dots(&data->img, &data->map);
	//draw_lines(&data->img, &data->map);
	// draw_dots(&data->img, data->map.values, data->map.num_rows, data->map.num_cols, data->map.a_x, data->map.a_z);
	// loop(&data->img, &data->map);

	// draw_dots(&data->img, &data->map);

	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);

	// last_a_z = data->map.a_z;
	// last_a_x = data->map.a_x;

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
	read_map(open("maps/42.fdf", O_RDONLY), &data.map);
	fill_z(open("maps/42.fdf", O_RDONLY), &data.map);
	cartesian_to_iso(&data.map);
	
	draw_lines(&data.img, &data.map);
	draw_dots(&data.img, &data.map);

	print_gradient(data.img.gradient);

	mlx_loop_hook(data.mlx_ptr, &render, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);

	mlx_loop(data.mlx_ptr);
	mlx_destroy_image(data.mlx_ptr, data.img.mlx_img);

	free(gradient);
	return (0);
}
