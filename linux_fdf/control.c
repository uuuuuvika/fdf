/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vshcherb <vshcherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 03:10:24 by vshcherb          #+#    #+#             */
/*   Updated: 2024/02/03 17:12:48 by vshcherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incl/fdf.h"

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		destroy_win_and_img(data);
	if (keysym == XK_Up)
		data->map.scale += 1.5;
	if (keysym == XK_Down)
		data->map.scale -= 1.5;
	if (keysym == XK_space)
		data->map.rotation_active = !data->map.rotation_active;
	if (keysym == XK_d)
		data->map.descale_z -= 0.01;
	if (keysym == XK_s)
		data->map.descale_z += 0.01;
	return (0);
}

int	close_window(t_data *data)
{
	destroy_win_and_img(data);
	return (0);
}

int	handle_mouse(int button, int x, int y, t_data *data)
{
	(void)x;
	(void)y;
	if (button == 1)
	{
		data->map.translate_active = !data->map.translate_active;
		mlx_mouse_get_pos(data->mlx_ptr, data->win_ptr,
			&data->mouse_x, &data->mouse_y);
	}
	return (0);
}
