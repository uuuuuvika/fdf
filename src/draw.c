/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vshcherb <vshcherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 14:37:56 by vshcherb          #+#    #+#             */
/*   Updated: 2024/02/04 19:14:44 by vshcherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incl/fdf.h"

void	draw_line(t_img *img, t_vector_vars vv)
{
	t_draw_vars	dv;
	float		position;
	int			x1;
	int			y1;

	x1 = vv.x;
	y1 = vv.y;
	init_draw_vars(&dv, &vv);
	while (!(x1 == vv.x_nxt && y1 == vv.y_nxt))
	{
		if (x1 >= 0 && x1 < WIDTH && y1 >= 0 && y1 < HEIGHT)
		{
			position = get_pix_position(vv, x1, y1);
			img_pix_put(img, x1, y1, get_clr(vv.clr, vv.clr_nxt, position));
		}
		adjust_direction(&dv, &x1, &y1);
	}
}

void	draw_lines(t_img *img, t_map *map)
{
	draw_horisontal_lines(img, map);
	draw_vertical_lines(img, map);
}

void	draw_horisontal_lines(t_img *img, t_map *map)
{
	int				x;
	int				y;
	t_vector_vars	dl;

	x = 0;
	while (x < map->num_rows)
	{
		y = 0;
		while (y < map->num_cols)
		{
			dl.x = map->coords[x][y].x_iso + WIDTH / 2;
			dl.y = map->coords[x][y].y_iso + HEIGHT / 2;
			dl.clr = map->coords[x][y].clr;
			if (x < map->num_rows - 1)
			{
				dl.x_nxt = map->coords[x + 1][y].x_iso + WIDTH / 2;
				dl.y_nxt = map->coords[x + 1][y].y_iso + HEIGHT / 2;
				dl.clr_nxt = map->coords[x + 1][y].clr;
				draw_line(img, dl);
			}
			y++;
		}
		x++;
	}
}

void	draw_vertical_lines(t_img *img, t_map *map)
{
	int				x;
	int				y;
	t_vector_vars	dl;

	x = 0;
	while (x < map->num_rows)
	{
		y = 0;
		while (y < map->num_cols)
		{
			dl.x = map->coords[x][y].x_iso + WIDTH / 2;
			dl.y = map->coords[x][y].y_iso + HEIGHT / 2;
			dl.clr = map->coords[x][y].clr;
			if (y < map->num_cols - 1)
			{
				dl.x_nxt = map->coords[x][y + 1].x_iso + WIDTH / 2;
				dl.y_nxt = map->coords[x][y + 1].y_iso + HEIGHT / 2;
				dl.clr_nxt = map->coords[x][y + 1].clr;
				draw_line(img, dl);
			}
			y++;
		}
		x++;
	}
}
