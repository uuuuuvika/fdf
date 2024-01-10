#include "fdf.h"

int handle_keypress(int key, t_data *data)
{
	if (key == KEY_ESC)
	{
		mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
		free(data->win_ptr);
		exit(0);
	}
	if (key == KEY_UP)
	{
		data->map.a_x += 0.05;
	}
	if (key == KEY_DOWN)
	{
		data->map.a_x -= 0.05;
	}
	if (key == KEY_LEFT)
	{
		data->map.a_z += 0.05;
	}
	if (key == KEY_RIGHT)
	{
		data->map.a_z -= 0.05;
	}
	return (0);
}

void get_mouse_position(int *x, int *y)
{
	CGEventRef event = CGEventCreate(NULL);
	CGPoint mouseLoc = CGEventGetLocation(event);
	*x = (int)mouseLoc.x;
	*y = (int)mouseLoc.y;
	printf("Mouse location: %f %f\n", mouseLoc.x, mouseLoc.y);
	CFRelease(event);
}


