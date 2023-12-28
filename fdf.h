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

#define RED_COEFFICIENT 0.2126;
#define GREEN_COEFFICIENT 0.7152;
#define BLUE_COEFFICIENT 0.0722;
#define DARK_THRESHOLD 128;


#define MLX_ERROR 1
#define KEY_ESC 53

typedef struct s_color
{
    int r;
    int g;
    int b;
} t_color;

typedef struct s_data
{
    void	*mlx_ptr;
    void	*win_ptr;
}	t_data;

t_color gradientColors[2];

int handle_keypress(int key, t_data *data);

int isDarkColor(t_color color);
void generateGradientPalette();

#endif