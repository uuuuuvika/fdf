#include "fdf.h"

int handle_keypress(int keysym, t_data *data)
{
	
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		exit(0);
	}
	if (keysym == XK_Up)
	{
		data->map.a_x -= 0.1;
	}
	if (keysym == XK_Down)
	{
		data->map.a_x += 0.1;
	}
	if (keysym == XK_Left)
	{
		data->map.a_z -= 0.1;
	}
	if (keysym == XK_Right)
	{
		data->map.a_z += 0.1;
	}
	return (0);
}