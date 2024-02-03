/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vshcherb <vshcherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 16:28:09 by vshcherb          #+#    #+#             */
/*   Updated: 2024/02/03 16:46:31 by vshcherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# define WIDTH				1200
# define HEIGHT				800

# define BUFFER_SIZE		1024

# define MLX_ERROR			1
# define MLX_SUCCESS		0

# define RED_COEFFICIENT	0.2126
# define GREEN_COEFFICIENT	0.7152
# define BLUE_COEFFICIENT	0.0722
# define DARK_THRESHOLD		128

# define GRAY				"\033[0;90m"
# define RED				"\033[0;91m"
# define GREEN				"\033[0;92m"
# define YELLOW				"\033[0;93m"
# define BLUE				"\033[0;94m"
# define MAGENTA			"\033[0;95m"
# define CYAN				"\033[0;96m"
# define WHITE				"\033[0;97m"

# define MSG "Usage: ./fdf <map>\nFor isometric projection: ./fdf <map>\nFor globe projection: ./fdf <map> globe\n"

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_render_vars
{
	float	last_a_z;
	float	last_a_x;
	float	last_scale;
	int		last_move_x;
	int		last_move_y;
	int		last_descale_z;
}	t_render_vars;

typedef struct s_draw_vars
{
	int	x1;
	int	y1;
	int	x2;
	int	y2;
	int	x1_start;
	int	y1_start;
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	err2;
}	t_draw_vars;

typedef struct s_vector_vars
{
	int		x;
	int		y;
	int		x_nxt;
	int		y_nxt;
	t_color	clr;
	t_color	clr_nxt;
}	t_vector_vars;

typedef struct s_coords
{
	int		value;
	float	x_iso;
	float	y_iso;
	t_color	color;
	float	r;
	float	theta;
	float	phi;
}	t_coords;

typedef struct transform_vars
{
	float	xx;
	float	yy;
	float	zz;
	int		relief;
}	t_transform_vars;

typedef struct s_map
{
	int			num_rows;
	int			num_cols;
	float		a_z;
	float		a_x;
	t_coords	**coords;
	float		scale;
	float		descale_z;
	bool		rotation_active;
	bool		translate_active;
	int			move_x;
	int			move_y;
	t_color		*gradient;
	int			max_val;
	int			min_val;
}	t_map;

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		mouse_x;
	int		mouse_y;
	t_img	img;
	t_map	map;
	char	*projection;
}	t_data;
#endif
