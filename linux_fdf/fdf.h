#ifndef FDF_H
#define FDF_H
#include <math.h>
#include <time.h>
#include <X11/X.h>
#include <X11/keysym.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include "libs/minilibx-linux/mlx.h"
#include "libs/the_libft/libft.h"

#define WIDTH 1100
#define HEIGHT 800

#define RED_COEFFICIENT 0.2126
#define GREEN_COEFFICIENT 0.7152
#define BLUE_COEFFICIENT 0.0722
#define DARK_THRESHOLD 128
#define BUFFER_SIZE 1024

#define GREEN_PIXEL 0xFF00
#define PURPLE_PIXEL 0xFF00FF
#define MLX_ERROR 1

typedef struct s_color
{
    int r;
    int g;
    int b;
} t_color;

typedef struct s_coords
{
    int value;
    double x_iso;
    double y_iso;
    t_color color;
} t_coords;

typedef struct s_map
{
    int num_rows;
    int num_cols;
    double a_z;
    double a_x;
    t_coords **coords;
    double scale;
    bool rotation_active;
    t_color *gradient; 
} t_map;

typedef struct s_img
{
    void *mlx_img;
    char *addr;
    int bpp;
    int line_len; //??
    int endian;
} t_img;

typedef struct s_data
{
    void *mlx_ptr;
    void *win_ptr;
    int mouse_x;
    int mouse_y;
    t_img img;
    t_map map;
} t_data;

int handle_keypress(int key, t_data *data);
void update_angle(double *angle, int old_position, int new_position, double increment);
void update_rotation(t_data  *data, double increment);

int is_dark(t_color color);
t_color *gen_gradient(void);
void print_gradient(t_color *gradient);
int gradient_to_int(t_color *color);
void colorize_points(t_map *map);

void img_pix_put(t_img *img, int x, int y, int color);

// map
void read_map(int fd, t_map *map);
void malloc_for_z(t_map *map);
void fill_z(int fd, t_map *map);
void free_arr2D(char **arr2D);
void cartesian_to_iso(t_map *map);

// draw
double get_pix_position(int x1, int x2, int y1, int y2, int x_cur, int y_cur);
void draw_l(t_img *img, int x1, int y1, int x2, int y2, t_color color1, t_color color2);
void draw_lines(t_img *img, t_map *map);


int destroy_win_and_img(t_data *data);

void draw_dots(t_img *img, t_map *map);

#endif
