/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vika <vika@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 03:10:24 by vshcherb          #+#    #+#             */
/*   Updated: 2024/08/08 00:46:32 by vika             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incl/fdf.h"

// int	handle_keypress(int keysym, t_data *data)
// {
// 	if (keysym == XK_Escape)
// 		destroy_win_and_img(data);
// 	if (keysym == XK_Up)
// 		data->map.scale += 1.5;
// 	if (keysym == XK_Down)
// 		data->map.scale -= 1.5;
// 	if (keysym == XK_space)
// 		data->map.rotation_active = !data->map.rotation_active;
// 	if (keysym == XK_d)
// 		data->map.descale_z -= 0.01;
// 	if (keysym == XK_s)
// 		data->map.descale_z += 0.01;
// 	return (0);
// }

int handle_keypress(int key, t_data *data)
{
	if (key == KEY_ESC)
		destroy_win_and_img(data);
	if (key == KEY_UP)
		data->map.scale += 0.5;
	if (key == KEY_DOWN)
		data->map.scale -= 0.5;
	if (key == SPACE)
		data->map.rotation_active = !data->map.rotation_active;
	if (key == KEY_A)
		data->map.translate_active = !data->map.translate_active;
	if (key == KEY_D)
		data->map.descale_z -= 0.01;
	if (key == KEY_S)
		data->map.descale_z += 0.01;
	return (0);
}

int	close_window(t_data *data)
{
	destroy_win_and_img(data);
	return (0);
}

void get_mouse_position(int *x, int *y)
{
	CGEventRef event = CGEventCreate(NULL);
	CGPoint mouseLoc = CGEventGetLocation(event);
	*x = (int)mouseLoc.x;
	*y = (int)mouseLoc.y;
	CFRelease(event);
}

int	handle_mouse(int button, int x, int y, t_data *data)
{
	(void)x;
	(void)y;
	// if (button == 1)
	// {
	// 	data->map.translate_active = !data->map.translate_active;
	// 	mlx_mouse_get_pos(data->mlx_ptr, data->win_ptr,
	// 		&data->mouse_x, &data->mouse_y);
	// }
	if (button == 1)
	{
		data->map.translate_active = !data->map.translate_active;
		get_mouse_position(&data->mouse_x, &data->mouse_y);
	}
	return (0);
}
