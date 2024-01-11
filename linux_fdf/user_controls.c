#include "fdf.h"

int handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		destroy_win_and_img(data);
	if (keysym == XK_Up)
		data->map.scale += 0.5;
	if (keysym == XK_Down)
		data->map.scale -= 0.5;
	if (keysym == XK_space)
		data->map.rotation_active = !data->map.rotation_active;
	return (0);
}

void update_angle(double *angle, int old_position, int new_position, double increment)
{
	if (new_position > old_position)
		*angle -= increment;
	else if (new_position < old_position)
		*angle += increment;
}

void update_rotation(t_data *data, double increment)
{
	static int mouse_x;
	static int mouse_y;

	if (!data->map.rotation_active)
		return;
	mlx_mouse_get_pos(data->mlx_ptr, data->win_ptr, &mouse_x, &mouse_y);
	update_angle(&data->map.a_z, data->mouse_x, mouse_x, increment);
	update_angle(&data->map.a_x, data->mouse_y, mouse_y, increment);
	data->mouse_x = mouse_x;
	data->mouse_y = mouse_y;
}
