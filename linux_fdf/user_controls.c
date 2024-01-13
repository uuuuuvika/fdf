#include "fdf.h"

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
	if (keysym == XK_Left)
		translate(data, 25.5);
	return (0);
}

int handle_mouse(int button, int x, int y, t_data *data)
{
	if (button == 1)
		data->map.translate_active = !data->map.translate_active;
	// data->mouse_x = x;
	printf("mouse_x: %d\n", x);
	// data->mouse_y = y;
	printf("mouse_y: %d\n", y);
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

void update_iso(int *iso, int old_position, int new_position, double increment)
{
	if (new_position > old_position)
		*iso += increment;
	else if (new_position < old_position)
		*iso -= increment;
}

void translate(t_data *data, double increment)
{
	// int i;
	// int j;
	static int mouse_x;
	static int mouse_y;
	

	if (!data->map.translate_active)
		return;

	mlx_mouse_get_pos(data->mlx_ptr, data->win_ptr, &mouse_x, &mouse_y);
	update_iso(&xo, data->mouse_x, mouse_x, increment);
	update_iso(&yo, data->mouse_y, mouse_y, increment);
	// i = 0;
	// while (i < data->map.num_rows)
	// {
	// 	j = 0;
	// 	while (j < data->map.num_cols)
	// 	{
	// 		printf("BEFORE:iso_x: %f, iso_y: %f\n", data->map.coords[i][j].x_iso, data->map.coords[i][j].y_iso);
	// 		update_iso(&data->map.coords[i][j].x_iso, data->mouse_x, mouse_x, increment);
	// 		update_iso(&data->map.coords[i][j].y_iso, data->mouse_y, mouse_y, increment);
	// 		printf("AFTER:iso_x: %f, iso_y: %f\n", data->map.coords[i][j].x_iso, data->map.coords[i][j].y_iso);
	// 		j++;
	// 	}
	// 	i++;
	// }
	data->mouse_x = mouse_x;
	data->mouse_y = mouse_y;
}
