#include "fdf.h"

void draw_dots(t_img *img, t_map *map)
{
	double xx, yy;
	int x, y;

	x = 0;

	while (x < map->num_rows)
	{
		y = 0;
		while (y < map->num_cols)
		{
			// z = map->coords[(int)x][(int)y].value;
			xx = map->coords[x][y].x_iso + WIDTH / 2;
			yy = map->coords[x][y].y_iso + HEIGHT / 2;

			if (xx >= 0 && xx <= WIDTH && yy >= 0 && yy <= HEIGHT)
				img_pix_put(img, xx, yy, PURPLE_PIXEL);
			y++;
		}
		x++;
	}
}
