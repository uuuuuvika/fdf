/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vika <vika@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 04:11:25 by vika              #+#    #+#             */
/*   Updated: 2024/02/03 13:32:07 by vika             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "incl/_fdf.h"

void	get_mouse_position(int *x, int *y);
int		handle_mousepress(int button, int x, int y, t_data *data);
int		handle_keypress(int key, t_data *data);
int		close_window(t_data *data);
void	rotate(t_data *data, float increment);
void	translate(t_data *data);

t_color	*gen_gradient(void);
void	colorize_points(t_map *map);
void	img_pix_put(t_img *img, int x, int y, int color);

int		handle_last_render_vars(t_render_vars *lrv, t_data *data);
int		read_map(int fd, t_map *map);
void	malloc_for_z(t_map *map);
void	fill_z(int fd, t_map *map);
void	free_temp_arrays(char **arr2D, char *line);

void	cartesian_to_iso(t_map *map);
void	create_map(char *argv, t_data *data, t_color *gradient);
void	cartesian_to_spherical(t_map *map);

void	find_extremes(t_map *map);
int		count_columns(char **cols);

float	get_pix_position(int x1, int x2, int y1, int y2, int x_cur, int y_cur);
void	draw_l(t_img *img, t_draw_lines_vars dl);
void	draw_lines(t_img *img, t_map *map);
void	draw_horisontal_lines(t_img *img, t_map *map);
void	draw_vertical_lines(t_img *img, t_map *map);
int		get_clr(t_color color1, t_color color2, float position);
void	adjust_direction(t_draw_vars *dv, int *x1, int *y1);
void	init_draw_vars(t_draw_vars *dv, t_draw_lines_vars *dl);

int		destroy_win_and_img(t_data *data);
t_color	hex_to_color(char *hex);

#endif
