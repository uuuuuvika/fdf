#include "fdf.h"

int	handle_keypress(int keysym, t_data *data)
{
    if (keysym == XK_space)
    {
        mlx_destroy_window(data->mlx_ptr, data->win_ptr);
        data->win_ptr = NULL;
    }
    return (0);
}

int	render(t_data *data)
{
    /* if window has been destroyed, we don't want to put the pixel ! */
    if (data->win_ptr != NULL)
        mlx_pixel_put(data->mlx_ptr, data->win_ptr, 
            WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, RED_PIXEL);
    return (0);
}

// int main()
// {
//     void *mlx = mlx_init();
// 	if (mlx == NULL)
// 		return (MLX_ERROR);
//     void *win = mlx_new_window(mlx, 640, 360, "jo, this is Window");
// 	if (win == NULL){
// 		free(win);
// 		return (MLX_ERROR);
// 	}
//     mlx_loop(mlx);\
// 	mlx_destroy_window(mlx, win);
// 	free(mlx);
// 	return (0);
// }

int	main(void)
{
    t_data	data;

    data.mlx_ptr = mlx_init();
    if (data.mlx_ptr == NULL)
        return (MLX_ERROR);
    data.win_ptr = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT,
                                "my window");
    if (data.win_ptr == NULL)
    {
        free(data.win_ptr);
        return (MLX_ERROR);
    }

    /* Setup hooks */ 
    mlx_loop_hook(data.mlx_ptr, &render, &data);
    mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);

    mlx_loop(data.mlx_ptr);

    /* we will exit the loop if there's no window left, and execute this code */
   // mlx_destroy_display(data.mlx_ptr);
    free(data.mlx_ptr);
}