/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vshcherb <vshcherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 03:10:41 by vshcherb          #+#    #+#             */
/*   Updated: 2024/02/03 03:10:59 by vshcherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int destroy_win_and_img(t_data *data) 
{
    if (data->img.mlx_img != NULL)
    {
        mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
        data->img.mlx_img = NULL;
    }
    if (data->win_ptr != NULL)
    {
        mlx_destroy_window(data->mlx_ptr, data->win_ptr);
        data->win_ptr = NULL;
    }
    if (data->mlx_ptr != NULL)
    {
        mlx_destroy_display(data->mlx_ptr);
        free(data->mlx_ptr);
        data->mlx_ptr = NULL;
    }
    if (data->map.coords != NULL)
    {
        while(data->map.num_rows--)
            free(data->map.coords[data->map.num_rows]);
        free(data->map.coords);
        data->map.coords = NULL;  
    }
    if (data->map.gradient != NULL)
    {
        free(data->map.gradient);
        data->map.gradient = NULL;
    }
    exit(0);
}

void	free_temp_arrays(char **arr2D, char *line)
{
	int	i;

	i = 0;
	while (arr2D[i] != NULL && arr2D[i][0] != '\n')
		free(arr2D[i++]);
	free(arr2D);
	free(line);
}

int	handle_last_render_vars(t_render_vars *lrv, t_data *data)
{
	lrv->last_a_z = data->map.a_z;
	lrv->last_a_x = data->map.a_x;
	lrv->last_scale = data->map.scale;
	lrv->last_move_x = data->map.move_x;
	lrv->last_move_y = data->map.move_y;
	lrv->last_descale_z = data->map.descale_z;
	return (0);
}

void	malloc_for_z(t_map *map)
{
	int	i;

	map->coords = malloc(sizeof(t_coords *) * map->num_rows);
	i = 0;
	while (i < map->num_rows)
	{
		map->coords[i] = malloc(sizeof(t_coords) * map->num_cols);
		i++;
	}
}

void	find_extremes(t_map *map)
{
	int	min_val;
	int	max_val;
	int	i;
	int	j;

	min_val = map->coords[0][0].value;
	max_val = map->coords[0][0].value;
	i = 0;
	while (i < map->num_rows)
	{
		j = 0;
		while (j < map->num_cols)
		{
			if (map->coords[i][j].value < min_val)
				min_val = map->coords[i][j].value;
			if (map->coords[i][j].value > max_val)
				max_val = map->coords[i][j].value;
			j++;
		}
		i++;
	}
	map->min_val = min_val;
	map->max_val = max_val;
}
