#ifndef FDF_HM
#define FDF_HM
#include <math.h>
#include <time.h>
#include <X11/X.h>
// #include <X11/keysym.h>
#include <CoreGraphics/CoreGraphics.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include "libs/minilibx_macos/mlx.h"
#include "libs/the_libft/libft.h"

#define WIDTH 1200
#define HEIGHT 800

#define RED_COEFFICIENT 0.2126
#define GREEN_COEFFICIENT 0.7152
#define BLUE_COEFFICIENT 0.0722
#define DARK_THRESHOLD 128
#define BUFFER_SIZE 1024

#define GREEN_PIXEL 0xFF00
#define PURPLE_PIXEL 0xFF00FF

#define MLX_ERROR 1

#define KEY_ESC 53
#define KEY_UP 126
#define KEY_DOWN 125
#define KEY_LEFT 123
#define KEY_RIGHT 124
#define KEY_W 13
#define KEY_S 1
#define KEY_D 2
#define KEY_A 0
#define SPACE 49

typedef struct s_render_vars
{
    float last_a_z;
    float last_a_x;
    float last_scale;
    int last_move_x;
    int last_move_y;
    int last_descale_z;
} t_render_vars;

typedef struct s_color
{
    int r;
    int g;
    int b;
} t_color;

typedef struct s_spherical
{
    float r;
    float theta;
    float phi;
} t_spherical;

typedef struct s_coords
{
    int value;
    float x_iso;
    float y_iso;
    t_color color;
    float r;
    float theta;
    float phi;
} t_coords;

typedef struct s_map
{
    int num_rows;
    int num_cols;
    float a_z;
    float a_x;
    t_coords **coords;
    float scale;
    float descale_z;
    bool rotation_active;
    bool translate_active;
    int move_x;
    int move_y;
    t_color *gradient;
    bool has_color;
    int max_val;
    int min_val;
} t_map;

typedef struct s_img
{
    void *mlx_img;
    char *addr;
    int bpp;
    int line_len;
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

void draw_circle(t_img *img, t_map *map);

void get_mouse_position(int *x, int *y);
int handle_mousepress(int button, int x, int y, t_data *data);
int handle_keypress(int key, t_data *data);

void rotate(t_data *data, float increment);
void translate(t_data *data);
void update_visuals(float *param, int old_position, int new_position, float increment);

int is_dark(t_color color);
t_color *gen_gradient(void);
void print_gradient(t_color *gradient);
int gradient_to_int(t_color *color);
void colorize_points(t_map *map);

void img_pix_put(t_img *img, int x, int y, int color);
int	handle_last_render_vars(t_render_vars *lrv, t_data *data);

// map
int read_map(int fd, t_map *map);
void malloc_for_z(t_map *map);
void fill_z(int fd, t_map *map);
void free_arr2D(char **arr2D, char *line);
void cartesian_to_iso(t_map *map);
void create_map(char *argv, t_data *data, t_color *gradient);
void cartesian_to_spherical(t_map *map);
void find_extremes(t_map *map);
int	read_first_line(int fd, int *num_cols);
int	read_next_line(int fd, int *num_cols);
int count_columns(char **cols);

// draw
float get_pix_position(int x1, int x2, int y1, int y2, int x_cur, int y_cur);
void draw_l(t_img *img, int x1, int y1, int x2, int y2, t_color color1, t_color color2);
void draw_lines(t_img *img, t_map *map);

int destroy_win_and_img(t_data *data);
t_color hex_to_color(char *hex);
void draw_dots(t_img *img, t_map *map);

#endif
