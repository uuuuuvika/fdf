/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vshcherb <vshcherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 15:12:25 by vshcherb          #+#    #+#             */
/*   Updated: 2024/02/03 15:19:35 by vshcherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incl/fdf.h"

float	get_pix_position(t_vector_vars vv, int x_cur, int y_cur)
{
	float	full_dist;
	float	dist_to_current;

	full_dist = hypot(vv.x_nxt - vv.x, vv.y_nxt - vv.y);
	dist_to_current = hypot(x_cur - vv.x, y_cur - vv.y);
	if (full_dist != 0.0)
		return (dist_to_current / full_dist);
	return (1.0);
}

int	get_clr(t_color clr_1, t_color clr_2, float position)
{
	int	r;
	int	g;
	int	b;

	r = round(clr_1.r * (1 - position) + clr_2.r * position);
	g = round(clr_1.g * (1 - position) + clr_2.g * position);
	b = round(clr_1.b * (1 - position) + clr_2.b * position);
	return ((r << 16) | (g << 8) | b);
}

void	init_draw_vars(t_draw_vars *dv, t_vector_vars *dl)
{
	dv->x1_start = dl->x;
	dv->y1_start = dl->y;
	dv->dx = abs(dl->x_nxt - dl->x);
	dv->dy = abs(dl->y_nxt - dl->y);
	if (dl->x < dl->x_nxt)
		dv->sx = 1;
	else
		dv->sx = -1;
	if (dl->y < dl->y_nxt)
		dv->sy = 1;
	else
		dv->sy = -1;
	dv->err = dv->dx - dv->dy;
}

void	adjust_direction(t_draw_vars *dv, int *x1, int *y1)
{
	int	direction;

	direction = 2 * dv->err;
	if (direction > -dv->dy)
	{
		dv->err -= dv->dy;
		*x1 += dv->sx;
	}
	if (direction < dv->dx)
	{
		dv->err += dv->dx;
		*y1 += dv->sy;
	}
}
