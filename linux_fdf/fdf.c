/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vshcherb <vshcherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 20:23:37 by vshcherb          #+#    #+#             */
/*   Updated: 2024/02/04 23:46:56 by vshcherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incl/fdf.h"

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
		compare_and_draw(data);
		handle_last_render_vars(&lrv, data);
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, 
			data->img.mlx_img, 0, 0);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	static t_data		data;

	if (argc < 2 || argc > 3 || (argc == 3 && ft_strcmp(argv[2], "globe") != 0))
	{
		ft_printf(YELLOW MSG WHITE);
		return (MLX_ERROR);
	}
	if (mlx_init_data(&data) == MLX_SUCCESS)
	{
		create_map(argv[1], &data);
		project_and_draw(argc, argv, &data);
		mlx_loop_hook(data.mlx_ptr, &render, &data);
		mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
		mlx_mouse_hook(data.win_ptr, &handle_mouse, &data);
		mlx_hook(data.win_ptr, 17, 1L << 17, close_window, &data);
		mlx_loop(data.mlx_ptr);
	}
	destroy_win_and_img(&data);
	return (0);
}
