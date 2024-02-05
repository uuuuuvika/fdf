/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vshcherb <vshcherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 17:11:14 by vshcherb          #+#    #+#             */
/*   Updated: 2024/02/03 17:17:03 by vshcherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incl/fdf.h"

static int	g_mouse_x;
static int	g_mouse_y;

void	update_rotation(float *param, int old_pos, int new_pos, float i)
{
	if (new_pos > old_pos)
		*param += i;
	else if (new_pos < old_pos)
		*param -= i;
}

void	update_translation(int *param, int old_position, int new_position)
{
	if (new_position > old_position)
		*param += new_position - old_position;
	else if (new_position < old_position)
		*param -= old_position - new_position;
}

void	rotate(t_data *data, float increment)
{
	if (!data->map.rotation_active)
		return ;
	data->mouse_x = g_mouse_x;
	data->mouse_y = g_mouse_y;
	mlx_mouse_get_pos(data->mlx_ptr, data->win_ptr, &g_mouse_x, &g_mouse_y);
	update_rotation(&data->map.a_z, data->mouse_x, g_mouse_x, increment);
	update_rotation(&data->map.a_x, data->mouse_y, g_mouse_y, increment);
	data->mouse_x = g_mouse_x;
	data->mouse_y = g_mouse_y;
}

void	translate(t_data *data)
{
	if (!data->map.translate_active)
		return ;
	mlx_mouse_get_pos(data->mlx_ptr, data->win_ptr, &g_mouse_x, &g_mouse_y);
	update_translation(&data->map.move_x, data->mouse_x, g_mouse_x);
	update_translation(&data->map.move_y, data->mouse_y, g_mouse_y);
	data->mouse_x = g_mouse_x;
	data->mouse_y = g_mouse_y;
}
