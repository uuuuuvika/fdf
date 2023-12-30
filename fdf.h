#ifndef FDF_H
# define FDF_H
# include <math.h>
# include <stdlib.h>
# include <time.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include "minilibx_macos/mlx.h"

#define WIDTH 800
#define HEIGHT 800

#define RED_COEFFICIENT 0.2126
#define GREEN_COEFFICIENT 0.7152
#define BLUE_COEFFICIENT 0.0722
#define DARK_THRESHOLD 128

#define GREEN_PIXEL 0xFF00

#define MLX_ERROR 1
#define KEY_ESC 53

typedef struct s_color
{
    int r;
    int g;
    int b;
} t_color;

typedef struct s_img
{
    void	*mlx_img;
    char	*addr;
    int		bpp; /* bits per pixel */
    int		line_len;
    int		endian;
    t_color *gradient;
}	t_img;

typedef struct s_data
{
    void	*mlx_ptr;
    void	*win_ptr;
    t_img	img;
}	t_data;


//functions 
int handle_keypress(int key, t_data *data);

int is_dark(t_color color);
t_color *gen_gradient(void);

void	img_pix_put(t_img *img, int x, int y, int color);

#endif