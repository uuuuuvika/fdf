#include "fdf.h"

static int mouse_x;
static int mouse_y;

int handle_keypress(int key, t_data *data)
{
	if (key == KEY_ESC)
		destroy_win_and_img(data);
	if (key == KEY_UP)
		data->map.scale += 0.5;
	if (key == KEY_DOWN)
		data->map.scale -= 0.5;
	if (key == SPACE)
		data->map.rotation_active = !data->map.rotation_active;
	if (key == KEY_A)
	{
		data->map.translate_active = !data->map.translate_active;
	}
	if (key == KEY_D)
		data->map.descale_z -= 0.01;
	if (key == KEY_S)
		data->map.descale_z += 0.01;
	return (0);
}

int handle_mousepress(int button, int x, int y, t_data *data)
{
	(void)x;
	(void)y;

	if (button == 1)
	{
		data->map.translate_active = !data->map.translate_active;
		get_mouse_position(&data->mouse_x, &data->mouse_y);
	}
	return (0);
}

int	close_window(t_data *data)
{
	destroy_win_and_img(data);
	return (0);
}

void get_mouse_position(int *x, int *y)
{
	CGEventRef event = CGEventCreate(NULL);
	CGPoint mouseLoc = CGEventGetLocation(event);
	*x = (int)mouseLoc.x;
	*y = (int)mouseLoc.y;
	CFRelease(event);
}

void	update_rotation(float *param, int old_position, int new_position, float increment)
{
	if (new_position > old_position)
		*param += increment;
	else if (new_position < old_position)
		*param -= increment;
}

void	update_translation(int *param, int old_position, int new_position)
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
	get_mouse_position(&mouse_x, &mouse_y);
	update_rotation(&data->map.a_z, data->mouse_x, mouse_x, increment);
	update_rotation(&data->map.a_x, data->mouse_y, mouse_y, increment);
	data->mouse_x = mouse_x;
	data->mouse_y = mouse_y;
}

void	translate(t_data *data)
{
	// static int mouse_x;
	// static int mouse_y;
	
	if (!data->map.translate_active)
		return;
	static int mouse_x;
	static int mouse_y;
	printf("mouse_x: %d\n", mouse_x);
	get_mouse_position(&mouse_x, &mouse_y);
	update_translation(&data->map.move_x, data->mouse_x, mouse_x);
	update_translation(&data->map.move_y, data->mouse_y, mouse_y);
	data->mouse_x = mouse_x;
	data->mouse_y = mouse_y;
}
