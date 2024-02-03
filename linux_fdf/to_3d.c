/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_to_3d.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vshcherb <vshcherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 03:10:13 by vshcherb          #+#    #+#             */
/*   Updated: 2024/02/03 17:04:11 by vshcherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incl/fdf.h"

void	cartesian_to_iso(t_map *map)
{
	int					x;
	int					y;
	t_transform_vars	tv;

	x = 0;
	while (x < map->num_rows)
	{
		y = 0;
		while (y < map->num_cols)
		{
			tv.relief = map->coords[x][y].value * map->descale_z;
			rotate_over_z(xwo(map, x), ywo(map, y), &tv, map->a_z);
			rotate_over_x(tv.yy, tv.relief, &tv.yy, map->a_x);
			map->coords[x][y].x_iso = tv.xx * map->scale + map->move_x;
			map->coords[x][y].y_iso = tv.yy * map->scale + map->move_y;
			y++;
		}
		x++;
	}
}

void	cartesian_to_spherical(t_map *map)
{
	int					x;
	int					y;
	t_transform_vars	tv;

	x = 0;
	while (x < map->num_rows)
	{
		y = 0;
		while (y < map->num_cols)
		{
			tv.relief = map->coords[x][y].value * map->descale_z;
			tv.xx = sin(M_PI * x / map->num_rows) * 
				cos(2 * M_PI * y / map->num_cols) * so(tv.relief);
			tv.yy = sin(M_PI * x / map->num_rows) 
				* sin(2 * M_PI * y / map->num_cols) * so(tv.relief);
			tv.zz = cos(M_PI * x / map->num_rows) * so(tv.relief);
			rotate_over_z(tv.xx, tv.yy, &tv, map->a_z);
			rotate_over_x(tv.yy, tv.zz, &tv.yy, map->a_x);
			map->coords[x][y].x_iso = tv.xx * map->scale * 10 + map->move_x;
			map->coords[x][y].y_iso = tv.yy * map->scale * 10 + map->move_y;
			y++;
		}
		x++;
	}
}
