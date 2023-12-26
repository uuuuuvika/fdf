#ifndef FDF_H
# define FDF_H
# include <math.h>
# include <stdlib.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include "minilibx_macos/mlx.h"

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 300

#define MLX_ERROR 1

#define RED_PIXEL 0xFF0000

typedef struct s_data
{
    void	*mlx_ptr;
    void	*win_ptr;
}	t_data;

#endif