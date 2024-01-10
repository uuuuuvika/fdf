#include "fdf.h"

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
	static double last_a_z;
	static double last_a_x;

	get_mouse_position(&mouse_x, &mouse_y);

	update_angle(&data->map.a_z, data->mouse_x, mouse_x, 0.05);
	update_angle(&data->map.a_x, data->mouse_y, mouse_y, 0.05);

	data->mouse_x = mouse_x;
	data->mouse_y = mouse_y;

	if (last_a_z != data->map.a_z || last_a_x != data->map.a_x)
	{
		mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
		data->img.mlx_img = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
		data->img.addr = mlx_get_data_addr(data->img.mlx_img, &data->img.bpp, &data->img.line_len, &data->img.endian);
		cartesian_to_iso(&data->map);
		draw_lines(&data->img, &data->map);
		last_a_z = data->map.a_z;
		last_a_x = data->map.a_x;
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
	get_mouse_position(&data.mouse_x, &data.mouse_y);
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
