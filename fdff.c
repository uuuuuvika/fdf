#include "fdf.h"
#include <stdlib.h>
#include "minilibx_macos/mlx.h"

// # define WINDOW_WIDTH 600
// # define WINDOW_HEIGHT 300



int main()
{
    void *mlx = mlx_init();
    void *win = mlx_new_window(mlx, 640, 360, "Tutorial Window");
    mlx_loop(mlx);
}