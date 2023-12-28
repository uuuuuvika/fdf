#include "fdf.h"

int handle_keypress(int key, t_data *data)
{
	if (key == KEY_ESC)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
		exit(0);
	}
	return (0);
}