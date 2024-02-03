/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vshcherb <vshcherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 02:01:58 by vshcherb          #+#    #+#             */
/*   Updated: 2024/02/03 03:09:05 by vshcherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float get_pix_position(int x1, int x2, int y1, int y2, int x_cur, int y_cur)
{
	float full_dist = hypot(x2 - x1, y2 - y1);
	float dist_to_current = hypot(x_cur - x1, y_cur - y1);
	if (full_dist != 0.0)
		return (dist_to_current / full_dist);
	return (1.0);
}

int get_clr(t_color color1, t_color color2, float position)
{
	int r;
	int g;
	int b;

	r = round(color1.r * (1 - position) + color2.r * position);
	g = round(color1.g * (1 - position) + color2.g * position);
	b = round(color1.b * (1 - position) + color2.b * position);
	return ((r << 16) | (g << 8) | b);
}

void init_draw_vars(t_draw_vars *dv, int x1, int y1, int x2, int y2)
{
	dv->x1_start = x1;
	dv->y1_start = y1;
	dv->dx = abs(x2 - x1);
	dv->dy = abs(y2 - y1);
	dv->sx = (x1 < x2) ? 1 : -1;
	dv->sy = (y1 < y2) ? 1 : -1;
	dv->err = dv->dx - dv->dy;
}

void adjust_direction(int *err, int *x1, int *y1, int *sx, int *sy, int *dx, int *dy)
{
	int	direction;

	direction = 2 * *err;
	if (direction > -*dy)
	{
		*err -= *dy;
		*x1 += *sx;
	}
	if (direction < *dx)
	{
		*err += *dx;
		*y1 += *sy;
	}
}

void draw_l(t_img *img, int x1, int y1, int x2, int y2, t_color color1, t_color color2)
{

	t_draw_vars	dv;
	float		position;

	init_draw_vars(&dv, x1, y1, x2, y2);
	while (!(x1 == x2 && y1 == y2))
	{
		if (x1 >= 0 && x1 < WIDTH && y1 >= 0 && y1 < HEIGHT)
		{
			position = get_pix_position(dv.x1_start, x2, dv.y1_start, y2, x1, y1);
			img_pix_put(img, x1, y1, get_clr(color1, color2, position));
		}
		adjust_direction(&dv.err, &x1, &y1, &dv.sx, &dv.sy, &dv.dx, &dv.dy);
	}
}


// void draw_lines(t_img *img, t_map *map)
// {
// 	int x;
// 	int y;
// 	t_draw_lines_vars dl;

// 	x = 0;
// 	while (x < map->num_rows)
// 	{
// 		y = 0;
// 		while (y < map->num_cols)
// 		{
// 			dl.x = map->coords[x][y].x_iso + WIDTH / 2;
// 			dl.y = map->coords[x][y].y_iso + HEIGHT / 2;
// 			dl.clr = map->coords[x][y].color;
// 			if (x < map->num_rows - 1)
// 			{
// 				dl.x_nxt = map->coords[x + 1][y].x_iso + WIDTH / 2;
// 				dl.y_nxt = map->coords[x + 1][y].y_iso + HEIGHT / 2;
// 				dl.clr_nxt = map->coords[x + 1][y].color;
// 				draw_l(img, dl.x, dl.y, dl.x_nxt, dl.y_nxt, dl.clr, dl.clr_nxt);
// 			}
// 			if (y < map->num_cols - 1)
// 			{
// 				dl.x_nxt = map->coords[x][y + 1].x_iso + WIDTH / 2;
// 				dl.y_nxt = map->coords[x][y + 1].y_iso + HEIGHT / 2;
// 				dl.clr_nxt = map->coords[x][y + 1].color;
// 				draw_l(img, dl.x, dl.y, dl.x_nxt, dl.y_nxt, dl.clr, dl.clr_nxt);
// 			}
// 			y++;
// 		}
// 		x++;
// 	}
// }

void draw_lines(t_img *img, t_map *map)
{
	draw_horisontal_lines(img, map);
	draw_vertical_lines(img, map);
}

void draw_horisontal_lines(t_img *img, t_map *map)
{
	int x;
	int y;
	t_draw_lines_vars dl;

	x = 0;
	while (x < map->num_rows)
	{
		y = 0;
		while (y < map->num_cols)
		{
			dl.x = map->coords[x][y].x_iso + WIDTH / 2;
			dl.y = map->coords[x][y].y_iso + HEIGHT / 2;
			dl.clr = map->coords[x][y].color;
			if (x < map->num_rows - 1)
			{
				dl.x_nxt = map->coords[x + 1][y].x_iso + WIDTH / 2;
				dl.y_nxt = map->coords[x + 1][y].y_iso + HEIGHT / 2;
				dl.clr_nxt = map->coords[x + 1][y].color;
				draw_l(img, dl.x, dl.y, dl.x_nxt, dl.y_nxt, dl.clr, dl.clr_nxt);
			}
			y++;
		}
		x++;
	}
}

void draw_vertical_lines(t_img *img, t_map *map)
{
	int x;
	int y;
	t_draw_lines_vars dl;

	x = 0;
	while (x < map->num_rows)
	{
		y = 0;
		while (y < map->num_cols)
		{
			dl.x = map->coords[x][y].x_iso + WIDTH / 2;
			dl.y = map->coords[x][y].y_iso + HEIGHT / 2;
			dl.clr = map->coords[x][y].color;
			if (y < map->num_cols - 1)
			{
				dl.x_nxt = map->coords[x][y + 1].x_iso + WIDTH / 2;
				dl.y_nxt = map->coords[x][y + 1].y_iso + HEIGHT / 2;
				dl.clr_nxt = map->coords[x][y + 1].color;
				draw_l(img, dl.x, dl.y, dl.x_nxt, dl.y_nxt, dl.clr, dl.clr_nxt);
			}
			y++;
		}
		x++;
	}
}