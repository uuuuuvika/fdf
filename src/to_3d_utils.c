/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_to_3d_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vshcherb <vshcherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 15:26:30 by vshcherb          #+#    #+#             */
/*   Updated: 2024/02/03 17:02:25 by vshcherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incl/fdf.h"

void	rotate_over_z(float x, float y, t_transform_vars *tv, float angle)
{
	tv->xx = x * cos(angle) - y * sin(angle);
	tv->yy = x * sin(angle) + y * cos(angle);
}

void	rotate_over_x(float y, float z, float *yy, float angle)
{
	*yy = y * cos(angle) + z * sin(angle);
}

int	xwo(t_map *map, int x)
{
	return (x - map->num_rows / 2);
}

int	ywo(t_map *map, int y)
{
	return (y - map->num_cols / 2);
}

float	so(int relief)
{
	return (1 + relief / 6000.0);
}
