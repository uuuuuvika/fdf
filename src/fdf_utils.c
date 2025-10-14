/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vshcherb <vshcherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 20:07:46 by vshcherb          #+#    #+#             */
/*   Updated: 2024/02/04 23:19:22 by vshcherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incl/fdf.h"

int	compare_and_draw(t_data *data)
{
	if (ft_strcmp(data->projection, "globe") == 0)
		cartesian_to_spherical(&data->map);
	else
		cartesian_to_iso(&data->map);
	draw_lines(&data->img, &data->map);
	return (0);
}

int	project_and_draw(int argc, char **argv, t_data *data)
{
	if (argc == 3 && strcmp(argv[2], "globe") == 0)
	{
		data->projection = "globe";
		cartesian_to_spherical(&data->map);
	}
	else if (argc == 2)
	{
		data->projection = "isometric";
		cartesian_to_iso(&data->map);
	}
	draw_lines(&data->img, &data->map);
	return (0);
}

int	mlx_init_data(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
		return (MLX_ERROR);
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT, "fdf");
	if (data->win_ptr == NULL)
		return (MLX_ERROR);
	data->img.mlx_img = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.mlx_img, &data->img.bpp, 
			&data->img.line_len, &data->img.endian);
	return (MLX_SUCCESS);
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
