#include "fdf.h"
#include <stdlib.h>
#include "minilibx_macos/mlx.h"

int main(void)
{
    void	*mlx_ptr;

    mlx_ptr = mlx_init();
    
    free(mlx_ptr);
}