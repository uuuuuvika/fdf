#include "fdf.h"

static int mouse_x;
static int mouse_y;

int handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		destroy_win_and_img(data);
	if (keysym == XK_Up)
		data->map.scale += 1.5;
	if (keysym == XK_Down)
		data->map.scale -= 1.5;
	if (keysym == XK_space)
		data->map.rotation_active = !data->map.rotation_active;
	if (keysym == XK_d)
		data->map.descale_z -= 0.01;
	if (keysym == XK_s)
		data->map.descale_z += 0.01;
	return (0);
}

int	close_window(t_data *data)
{
	destroy_win_and_img(data);
	return (0);
}

int handle_mouse(int button, int x, int y, t_data *data)
{
	(void)x;
	(void)y;

	if (button == 1)
	{
		data->map.translate_active = !data->map.translate_active;
		mlx_mouse_get_pos(data->mlx_ptr, data->win_ptr, &data->mouse_x, &data->mouse_y);
	}
	return (0);
}

void update_rotation(float *param, int old_position, int new_position, float increment)
{
	if (new_position > old_position)
		*param += increment;
	else if (new_position < old_position)
		*param -= increment;
}

void update_translation(int *param, int old_position, int new_position)
{
	if (new_position > old_position)
		*param += new_position - old_position;
	else if (new_position < old_position)
		*param -= old_position - new_position;
}



void	rotate(t_data *data, float increment)
{
	if (!data->map.rotation_active)
		return;
	data->mouse_x = mouse_x;
	data->mouse_y = mouse_y;
	mlx_mouse_get_pos(data->mlx_ptr, data->win_ptr, &mouse_x, &mouse_y);
	update_rotation(&data->map.a_z, data->mouse_x, mouse_x, increment);
	update_rotation(&data->map.a_x, data->mouse_y, mouse_y, increment);
	data->mouse_x = mouse_x;
	data->mouse_y = mouse_y;
}

void	translate(t_data *data)
{
	if (!data->map.translate_active)
		return ;
	mlx_mouse_get_pos(data->mlx_ptr, data->win_ptr, &mouse_x, &mouse_y);
	update_translation(&data->map.move_x, data->mouse_x, mouse_x);
	update_translation(&data->map.move_y, data->mouse_y, mouse_y);
	data->mouse_x = mouse_x;
	data->mouse_y = mouse_y;
}
