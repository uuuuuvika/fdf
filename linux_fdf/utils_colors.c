/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vshcherb <vshcherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 03:10:30 by vshcherb          #+#    #+#             */
/*   Updated: 2024/02/03 17:29:51 by vshcherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incl/fdf.h"

int	is_contrast(t_color color1, t_color color2)
{
	int	brightness1;
	int	brightness2;

	brightness1 = color1.r * RED_COEFFICIENT + color1.g
		* GREEN_COEFFICIENT + color1.b * BLUE_COEFFICIENT; 
	brightness2 = color2.r * RED_COEFFICIENT + color2.g
		* GREEN_COEFFICIENT + color2.b * BLUE_COEFFICIENT;
	return (abs(brightness1 - brightness2) > DARK_THRESHOLD);
}

t_color	*gen_gradient(void)
{
	t_color	*gradients;

	srand(time(NULL));
	gradients = malloc(2 * sizeof(t_color));
	if (gradients == NULL)
		return (NULL);
	do
	{
	gradients[0].r = rand() % 256;
	gradients[0].g = rand() % 256;
	gradients[0].b = rand() % 256;
	gradients[1].r = rand() % 256;
	gradients[1].g = rand() % 256;
	gradients[1].b = rand() % 256;
	}
	while (!is_contrast(gradients[0], gradients[1]));
	return (gradients);
}

void	colorize_points(t_map *map)
{
	float	step;
	int		i;
	int		j;

	i = 0;
	while (i < map->num_rows)
	{
		j = 0;
		while (j < map->num_cols)
		{
			if (map->min_val == map->max_val)
				map->coords[i][j].color = map->gradient[0];
			else
			{
				step = (float)(map->coords[i][j].value - map->min_val) / (map->max_val - map->min_val);
				map->coords[i][j].color.r = map->gradient[0].r + step * (map->gradient[1].r - map->gradient[0].r);
				map->coords[i][j].color.g = map->gradient[0].g + step * (map->gradient[1].g - map->gradient[0].g);
				map->coords[i][j].color.b = map->gradient[0].b + step * (map->gradient[1].b - map->gradient[0].b);
			}
			j++;
		}
		i++;
	}
}
