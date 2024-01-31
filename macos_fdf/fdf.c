#include "fdf.h"

int	render(t_data *data)
{
	static t_render_vars	lrv;

	if (data->win_ptr == NULL)
		return (MLX_ERROR);
	rotate(data, 0.05);
	translate(data);
	if (lrv.last_a_z != data->map.a_z || lrv.last_a_x != data->map.a_x 
		|| lrv.last_scale != data->map.scale 
		|| lrv.last_move_x != data->map.move_x 
		|| lrv.last_move_y != data->map.move_y 
		|| lrv.last_descale_z != data->map.descale_z)
	{
		mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
		data->img.mlx_img = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
		data->img.addr = mlx_get_data_addr(data->img.mlx_img, &data->img.bpp, 
			&data->img.line_len, &data->img.endian);
		if (strcmp(data->projection, "globe") == 0)
			cartesian_to_spherical(&data->map);
		else
			cartesian_to_iso(&data->map);
		draw_lines(&data->img, &data->map);
		handle_last_render_vars(&lrv, data);
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
	}
	return (0);
}

int main(int argc, char **argv)
{
	static t_data	data; //???
	t_color			*gradient;

	gradient = gen_gradient();
	if (argc < 2 || argc > 3)
	{
		printf("__USAGE___\nFor isometric projection: ./fdf <map>\nFor globe projection: ./fdf <map> globe\n");
		return (MLX_ERROR);
	}
	if (gradient == NULL)
		return (MLX_ERROR);

	data.mlx_ptr = mlx_init();

	if (data.mlx_ptr == NULL)
		return (MLX_ERROR);

	data.win_ptr = mlx_new_window(data.mlx_ptr, WIDTH, HEIGHT, "FDF");

	if (data.win_ptr == NULL)
		return (MLX_ERROR);

	data.img.mlx_img = mlx_new_image(data.mlx_ptr, WIDTH, HEIGHT);
	data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp, &data.img.line_len, &data.img.endian);
	
	create_map(argv[1], &data, gradient);

	if (argc == 3 && strcmp(argv[2], "globe") == 0)
	{
		data.projection = "globe";
		cartesian_to_spherical(&data.map);
	}
	else if (argc == 2)
	{
		data.projection = "isometric";
		cartesian_to_iso(&data.map);
	}
	else
	{
		printf("Wrong arguments:(\nFor isometric projection: ./fdf <map>\nFor globe projection: ./fdf <map> globe\n");
		return (MLX_ERROR);
	}

	draw_lines(&data.img, &data.map);

	mlx_loop_hook(data.mlx_ptr, &render, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
	mlx_mouse_hook(data.win_ptr, &handle_mousepress, &data);
	mlx_hook(data.win_ptr, 17, 1L << 17, close_window, &data);
	mlx_loop(data.mlx_ptr);

	free(gradient);
	destroy_win_and_img(&data);
	return (0);
}
