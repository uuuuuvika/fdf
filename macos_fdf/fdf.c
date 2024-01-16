#include "fdf.h"

int render(t_data *data)
{
	static double last_a_z;
	static double last_a_x;
	static double last_scale;
	static int last_move_x;
	static int last_move_y;
	static int last_descale_z;

	if (data->win_ptr == NULL)
		return (MLX_ERROR);

	rotate(data, 0.05);
	translate(data);

	if (last_a_z != data->map.a_z || last_a_x != data->map.a_x || last_scale != data->map.scale || last_move_x != data->map.move_x || last_move_y != data->map.move_y || last_descale_z != data->map.descale_z)
	{
		mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
		data->img.mlx_img = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
		data->img.addr = mlx_get_data_addr(data->img.mlx_img, &data->img.bpp, &data->img.line_len, &data->img.endian);
		cartesian_to_iso(&data->map);
		//draw_dots(&data->img, &data->map);
		draw_lines(&data->img, &data->map);
		last_a_z = data->map.a_z;
		last_a_x = data->map.a_x;
		last_scale = data->map.scale;
		last_move_x = data->map.move_x;
		last_move_y = data->map.move_y;
		last_descale_z = data->map.descale_z;
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
	}
	return (0);
}

int main(int argc, char **argv)
{
	static t_data data; //???
	t_color *gradient = gen_gradient();

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
		free(data.win_ptr);
		return (MLX_ERROR);
	}

	data.img.mlx_img = mlx_new_image(data.mlx_ptr, WIDTH, HEIGHT);
	data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp, &data.img.line_len, &data.img.endian);
	data.map.gradient = gradient;

	create_map(argv[1], &data, gradient);
	cartesian_to_iso(&data.map);

	//draw_dots(&data.img, &data.map);
	draw_lines(&data.img, &data.map);

	print_gradient(data.map.gradient);

	mlx_loop_hook(data.mlx_ptr, &render, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
	//mlx_mouse_hook(data.win_ptr, &handle_mousepress, &data);

	mlx_loop(data.mlx_ptr);

	free(gradient);
	destroy_win_and_img(&data);
	// return (0);
}
