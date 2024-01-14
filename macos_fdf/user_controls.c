#include "fdf.h"

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
	if (key == KEY_LEFT)
		data->map.move_x -= 10;
	if (key == KEY_RIGHT)
		data->map.move_x += 10;
	// 	data->move_x -= 100;
	// if (key == KEY_RIGHT)
	// 	data->move_x += 100;

	return (0);
}

void get_mouse_position(int *x, int *y)
{
	CGEventRef event = CGEventCreate(NULL);
	CGPoint mouseLoc = CGEventGetLocation(event);
	*x = (int)mouseLoc.x;
	*y = (int)mouseLoc.y;
	//printf("Mouse location: %f %f\n", mouseLoc.x, mouseLoc.y);
	CFRelease(event);
}

void update_angle(double *angle, int old_position, int new_position, double increment)
{
	if (new_position > old_position)
		*angle -= increment;
	else if (new_position < old_position)
		*angle += increment;
}

void update_rotation(t_data  *data, double increment)
{
    static int mouse_x;
    static int mouse_y;

    if (!data->map.rotation_active)
        return ;
		
    get_mouse_position(&mouse_x, &mouse_y);
    update_angle(&data->map.a_z, data->mouse_x, mouse_x, increment);
    update_angle(&data->map.a_x, data->mouse_y, mouse_y, increment);
    data->mouse_x = mouse_x;
    data->mouse_y = mouse_y;
}


