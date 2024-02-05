/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vshcherb <vshcherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 19:11:40 by vshcherb          #+#    #+#             */
/*   Updated: 2024/02/04 20:11:14 by vshcherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incl/fdf.h"

void	clrize_point(t_map *map, int x, int y)
{
	float	step;

	if (map->min_val == map->max_val)
		map->coords[x][y].clr = map->gr[0];
	else
	{
		step = (float)(map->coords[x][y].value - map->min_val) / \
			(map->max_val - map->min_val);
		map->coords[x][y].clr.r = map->gr[0].r + step 
			* (map->gr[1].r - map->gr[0].r);
		map->coords[x][y].clr.g = map->gr[0].g + step 
			* (map->gr[1].g - map->gr[0].g);
		map->coords[x][y].clr.b = map->gr[0].b + step 
			* (map->gr[1].b - map->gr[0].b);
	}
}

void	clrize_points(t_map *map)
{
	int		i;
	int		j;

	i = 0;
	while (i < map->num_rows)
	{
		j = 0;
		while (j < map->num_cols)
		{
			clrize_point(map, i, j);
			j++;
		}
		i++;
	}
}

void	clrise_globe(t_map *map, int x, int y, int relief)
{
	if (relief < -300)
		map->coords[x][y].clr = hex_to_clr("0x02198B");
	else if (relief < -200)
		map->coords[x][y].clr = hex_to_clr("0x006789");
	else if (relief < -100)
		map->coords[x][y].clr = hex_to_clr("0x00bfff");
	else if (relief < 0)
		map->coords[x][y].clr = hex_to_clr("0x62d8ff");
	else if (relief < 100)
		map->coords[x][y].clr = hex_to_clr("0xF1B04C");
	else if (relief < 200)
		map->coords[x][y].clr = hex_to_clr("0xF4D03F");
	else
		map->coords[x][y].clr = hex_to_clr("0x900603");
}
