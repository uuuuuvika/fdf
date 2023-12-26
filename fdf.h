#ifndef FDF_H
# define FDF_H
# include <math.h>
# include <stdlib.h>
# include <time.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include "minilibx_macos/mlx.h"


#define WIDTH 800
#define HEIGHT 600



const double RED_COEFFICIENT = 0.2126;
const double GREEN_COEFFICIENT = 0.7152;
const double BLUE_COEFFICIENT = 0.0722;
const int DARK_THRESHOLD = 128;


#define MLX_ERROR 1


typedef struct
{
    int r;
    int g;
    int b;
} Color;

typedef struct s_data
{
    void	*mlx_ptr;
    void	*win_ptr;
}	t_data;

#endif