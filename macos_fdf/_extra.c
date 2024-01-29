#include "fdf.h"

void draw_dots(t_img *img, t_map *map)
{
	float xx, yy;
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

// void cartesian_to_iso(t_map *map)
// {
// 	int x;
// 	int y;
// 	int z;
// 	float xx;
// 	float yy;
// 	int off_x = map->num_rows / 2;
// 	int off_y = map->num_cols / 2;

// 	x = 0;
// 	while (x < map->num_rows)
// 	{
// 		y = 0;
// 		while (y < map->num_cols)
// 		{
// 			z = map->coords[x][y].value * map->descale_z;
// 			xx = (x - off_x) * cos(map->a_z) - (y - off_y) * sin(map->a_z);
// 			yy = ((x - off_x) * sin(map->a_z) + (y - off_y) * cos(map->a_z)) * cos(map->a_x) - z * sin(map->a_x);
// 			// yy = yy * cos(map->a_x) - z * sin(map->a_x);
// 			// map->coords[x][y].r = sqrt(xx * xx + yy * yy + z * z);

// 			// printf("x: %d, y: %d, xx: %f, yy: %f\n", x - off_x, y - off_y, xx, yy);

// 			map->coords[x][y].x_iso = xx * map->scale + map->move_x;
// 			map->coords[x][y].y_iso = yy * map->scale + map->move_y;
// 			y++;
// 		}
// 		x++;
// 	}
// }


// void cartesian_to_spherical(t_map *map)
// {
// 	int x;
// 	int y;
// 	// int z;
// 	// int off_x = map->num_rows / 2;
// 	// int off_y = map->num_cols / 2;
// 	float xx = 0;
// 	float yy = 0;
// 	float zz = 0;

// 	int off_x = map->num_rows / 2;
// 	int off_y = map->num_cols / 2;

// 	x = 0;
// 	while (x < map->num_rows)
// 	{
// 		y = 0;
// 		while (y < map->num_cols)
// 		{
// 			// float r = sqrt(x * x + y * y + z * z);
// 			int z = map->coords[x][y].value * map->descale_z;

// 			// rho must be positive
// 			// theta must be between 0 and 2pi
// 			// phi must be between 0 and pi

// 			// 	x = rho sin (phi) cos (theta)
// 			//	y = rho sin (phi) sin (theta)

// 			// z = rho cos (phi)
// 			// r = rho sin (phi)

// 			// circle with offset
// 			// int z = map->coords[x][y].value * map->descale_z;
// 			int r = sqrt((x - off_x) * (x - off_x) + (y - off_y) * (y - off_y));
// 			// printf("z: %d, r: %d\n", z, r);
// 			double theta = atan2(y - off_y, x - off_x);
// 			// double phi = atan2(z, r);
// 			// printf("theta: %f\n", theta);
// 			// double s = (z * 1) / r;
// 			// printf("s: %f\n", s);
// 			//  double theta_degrees = theta * (180.0 / M_PI);
// 			//  printf("theta: %f\n\n", theta_degrees);

// 			// xx = r * cos(2 * M_PI * theta);
// 			// yy = r * sin(2 * M_PI * theta);
// 			// zz = r * cos(M_PI * theta);

// 			xx = sin(M_PI * x / map->num_rows) * cos(2 * M_PI * y / map->num_cols);

// 			yy = sin(M_PI * x / map->num_rows) * sin(2 * M_PI * y / map->num_cols);
// 			zz = cos(M_PI * x / map->num_rows);

// 			// xx = (xx) * cos(map->a_z) - (yy) * sin(map->a_z);
// 			//  yy = ((xx) * sin(map->a_z) + (yy) * cos(map->a_z)) * cos(map->a_x) - zz * sin(map->a_x);

// 			yy = yy * cos(map->a_x) - zz * sin(map->a_x);
// 			// zz = cos(M_PI * x / map->num_rows);
// 			// printf ("zz: %f\n", zz);

// 			// xx = sin(M_PI * x / (map->num_rows)) * cos(2 * M_PI * y / (map->num_cols));
// 			// yy = sin(M_PI * x / (map->num_rows)) * sin(2 * M_PI * y / (map->num_cols));
// 			// int theta = 2 * M_PI * y / (map->num_cols);

// 			// zz = cos(M_PI * x / (map->num_rows));
// 			// double phi = atan(zz);
// 			// zz = r * cos(M_PI * (theta));

// 			// zz = r * cos(M_PI * s);

// 			// xx = xx * cos(map->a_z) - yy * sin(map->a_z);
// 			// yy = (xx * sin(map->a_z) + yy * cos(map->a_z)) - zz;
// 			// yy = yy * cos(map->a_x) - zz * sin(map->a_x);

// 			// printf("x: %d, y: %d, xx: %f, yy: %f\n", x, y, xx, yy);

// 			map->coords[x][y].x_iso = xx * map->scale + map->move_x;
// 			map->coords[x][y].y_iso = yy * map->scale + map->move_y;
// 			y++;
// 		}
// 		x++;
// 	}
// }

// void cartesian_to_spherical(t_map *map)
// {
// 	int x;
// 	int y;
// 	// int z;
// 	float xx = 0;
// 	float yy = 0;
// 	float zz = 0;

// 	int off_x = map->num_rows / 2;
// 	int off_y = map->num_cols / 2;

// 	x = 0;
// 	while (x < map->num_rows)
// 	{
// 		y = 0;
// 		while (y < map->num_cols)
// 		{
// 			int relief = map->coords[x][y].value * map->descale_z;

// 			if (relief < 0)
// 				map->coords[x][y].color = hex_to_color("0x0000FF");

// 			// xx = sin(M_PI * x / map->num_rows) * cos(2 * M_PI * y / map->num_cols);
// 			// yy = sin(M_PI * x / map->num_rows) * sin(2 * M_PI * y / map->num_cols);
// 			// zz = cos(M_PI * x / map->num_rows) + relief / 1000.0;

// 			float theta = M_PI * x / map->num_rows;	  // Latitude
// 			float phi = 2 * M_PI * y / map->num_cols; // Longitude

// 			xx = sin(theta) * cos(phi);
// 			yy = sin(theta) * sin(phi);
// 			zz = cos(theta) * (1 + relief / 800.0);

// 			// // rotation
// 			// yy = yy * cos(map->a_x) - zz * sin(map->a_x);
// 			// // xx = xx * cos(map->a_z) - yy * sin(map->a_z);
// 			// // yy = (xx * sin(map->a_z) + yy * cos(map->a_z)) * cos(map->a_x) - zz * sin(map->a_x);

// 			// map->coords[x][y].x_iso = xx * map->scale + map->move_x;
// 			// map->coords[x][y].y_iso = yy * map->scale + map->move_y;
// 			float temp_x = xx * cos(map->a_z) - yy * sin(map->a_z);
// 			float temp_y = xx * sin(map->a_z) + yy * cos(map->a_z);
// 			float temp_z = zz;

// 			// Apply rotations if needed (similar to what you did with yy)
// 			yy = temp_y * cos(map->a_x) - temp_z * sin(map->a_x);

// 			// Set the coordinates
// 			map->coords[x][y].x_iso = temp_x * map->scale + map->move_x;
// 			map->coords[x][y].y_iso = yy * map->scale + map->move_y;
// 			y++;
// 		}
// 		x++;
// 	}
// }

// void draw_base_line(t_img *img, t_map *map, int x1, int y1, int x2, int y2)
// {
// 	int dx = abs(x2 - x1);
// 	int dy = abs(y2 - y1);
// 	int sx = (x1 < x2) ? 1 : -1;
// 	int sy = (y1 < y2) ? 1 : -1;
// 	int err = dx - dy;
// 	int err2;

// 	while (!(x1 == x2 && y1 == y2))
// 	{
// 		if (1 >= 0 && x1 <= WIDTH && y1 >= 0 && y1 <= HEIGHT)
// 			img_pix_put(img, x1, y1, gradient_to_int(&map->gradient[1]));
// 		err2 = 2 * err;
// 		if (err2 > -dy)
// 		{
// 			err -= dy;
// 			x1 += sx;
// 		}
// 		if (err2 < dx)
// 		{
// 			err += dx;
// 			y1 += sy;
// 		}
// 	}
// }

// void draw_far_line(t_img *img, t_map *map, int x1, int y1, int x2, int y2)
// {
// 	int dx = abs(x2 - x1);
// 	int dy = abs(y2 - y1);
// 	int sx = (x1 < x2) ? 1 : -1;
// 	int sy = (y1 < y2) ? 1 : -1;
// 	int err = dx - dy;
// 	int err2;

// 	while (!(x1 == x2 && y1 == y2))
// 	{
// 		if (1 >= 0 && x1 <= WIDTH && y1 >= 0 && y1 <= HEIGHT)
// 			img_pix_put(img, x1, y1, gradient_to_int(&map->gradient[0]));
// 		err2 = 2 * err;
// 		if (err2 > -dy)
// 		{
// 			err -= dy;
// 			x1 += sx;
// 		}
// 		if (err2 < dx)
// 		{
// 			err += dx;
// 			y1 += sy;
// 		}
// 	}
// }

// void draw_line(t_img *img, t_map *map, int x1, int y1, int x2, int y2)
// {
// 	int x1_start = x1;
// 	int y1_start = y1;

// 	int dx = abs(x2 - x1);
// 	int dy = abs(y2 - y1);
// 	int sx = (x1 < x2) ? 1 : -1;
// 	int sy = (y1 < y2) ? 1 : -1;
// 	int err = dx - dy;
// 	int err2;

// 	while (!(x1 == x2 && y1 == y2))
// 	{
// 		if (x1 >= 0 && x1 <= WIDTH && y1 >= 0 && y1 <= HEIGHT)
// 		{
// 			float position = get_pix_position(x1_start, x2, y1_start, y2, x1, y1);
// 			int r = round(map->gradient[0].r * (1 - position) + map->gradient[1].r * position);
// 			int g = round(map->gradient[0].g * (1 - position) + map->gradient[1].g * position);
// 			int b = round(map->gradient[0].b * (1 - position) + map->gradient[1].b * position);
// 			int color = (r << 16) | (g << 8) | b;
// 			img_pix_put(img, x1, y1, color);
// 		}

// 		err2 = 2 * err;
// 		if (err2 > -dy)
// 		{
// 			err -= dy;
// 			x1 += sx;
// 		}
// 		if (err2 < dx)
// 		{
// 			err += dx;
// 			y1 += sy;
// 		}
// 	}
// }


// void draw_lines(t_img *img, t_map *map)
// {
// 	int x;
// 	int y;
// 	float nx_next;
// 	float ny_next;
// 	float nz_next;
// 	float nx;
// 	float ny;
// 	//int nz;

// 	x = 0;
// 	while (x < map->num_rows)
// 	{
// 		y = 0;
// 		while (y < map->num_cols)
// 		{
// 			nx = map->coords[x][y].x_iso + WIDTH / 2;
// 			ny = map->coords[x][y].y_iso + HEIGHT / 2;
// 			//nz = map->coords[x][y].value;
// 			t_color color = map->coords[x][y].color;

// 			if (x < map->num_rows - 1)
// 			{
// 				nx_next = map->coords[x + 1][y].x_iso + WIDTH / 2;
// 				ny_next = map->coords[x + 1][y].y_iso + HEIGHT / 2;
// 				//nz_next = map->coords[x + 1][y].value;
// 				t_color color_next = map->coords[x + 1][y].color;
				
// 				// if (nz == nz_next && nz == 0)
// 				// 	draw_base_line(img, map, nx, ny, nx_next, ny_next);

// 				// else if (nz == nz_next)
// 				// 	draw_far_line(img, map, nx, ny, nx_next, ny_next);

// 				// else if (nz > nz_next)
// 				// 	draw_line(img, map, nx, ny, nx_next, ny_next);
// 				// else
//                 //    draw_line(img, map, nx_next, ny_next, nx, ny);
// 				draw_l(img, map, nx, ny, nx_next, ny_next, color, color_next);
// 			}
// 			if (y < map->num_cols - 1)
// 			{
// 				nx_next = map->coords[x][y + 1].x_iso + WIDTH / 2;
// 				ny_next = map->coords[x][y + 1].y_iso + HEIGHT / 2;
// 				//nz_next = map->coords[x][y + 1].value;
// 				t_color color_next = map->coords[x][y + 1].color;
// 				// if (nz == nz_next && nz == 0)
// 				// 	draw_base_line(img, map, nx, ny, nx_next, ny_next);
// 				// else if (nz == nz_next)
// 				// 	draw_far_line(img, map, nx, ny, nx_next, ny_next);
// 				// else if (nz > nz_next)
// 				// 	draw_line(img, map, nx, ny, nx_next, ny_next);
// 				// else
//                 //    draw_line(img, map, nx_next, ny_next, nx, ny);
// 				draw_l(img, map, nx, ny, nx_next, ny_next, color, color_next);
// 			}
// 			y++;
// 		}
// 		x++;
// 	}
// }

void draw_circle(t_img *img, t_map *map)
{
	int x;
	int y;
	float xx = 0;
	float yy = 0;
	

	float	off_x = map->num_rows / 2;
	float	off_y = map->num_cols / 2;

	x = 0;
	while (x < map->num_rows)
	{
		y = 0;
		while (y < map->num_cols)
		{
			int z = map->coords[x][y].value * map->descale_z;

			int r = sqrt((x - off_x) * (x - off_x) + (y - off_y) * (y - off_y)); //-2 -2  -2 -1  -2 0  -2 1  -2 2 
			// r = r * 40 + z * 2;

			printf("z: %d, r: %d\n", z, r);
			//int r2 = 1 * 20;

			// int r3 = sqrt(y * y + x * x ) * 20;
			// printf("r3: %d\n", r3);

			double theta = atan2(y - off_y, x - off_x);
			//printf("theta: %f\n", theta);

			// double theta_degrees = theta * (180.0 / M_PI);
			// printf("theta: %f\n\n", theta_degrees);
        		
			xx = r * cos(2 * M_PI * (theta));
            yy = r * sin(2 * M_PI * (theta));
			//printf("x: %d, y: %d, xx: %f, yy: %f\n", x, y, xx, yy);
			
			//z = r * cos(M_PI * (theta));

			xx = xx * cos(map->a_z) - yy * sin(map->a_z);
			yy = (xx * sin(map->a_z) + yy * cos(map->a_z)) * cos(map->a_x) * sin(map->a_x);

 			xx = xx * map->scale + map->move_x;
			yy = yy * map->scale + map->move_y;

			img_pix_put(img, xx + WIDTH / 2, yy + HEIGHT / 2, PURPLE_PIXEL);

			// xx = r3 * cos(2 * M_PI * (theta));
            // yy = r3 * sin(2 * M_PI * (theta));
			// img_pix_put(img, xx + WIDTH / 2, yy + HEIGHT / 2, PURPLE_PIXEL);
			y++;
		}
		x++;
	}
}

int ipart(float x) {
    return (int)floor(x);
}
float fpart(float x) {
    return x - ipart(x);
}

float rfpart(float x) {
    return 1 - fpart(x);
}

float lerp(float start, float end, float t) {
    return start + t * (end - start);
}
// Function to plot the pixel at (x, y) with a color gradient
void plot(t_img *img, int x, int y, t_color *color)
{
    img_pix_put(img, y, x, (color->r << 16) | (color->g << 8) | color->b);
    printf("Plotting pixel at (%d, %d) with color (%d, %d, %d)\n", x, y, color->r, color->g, color->b);
}

// Function to draw a line with a color gradient from color1 to color2
void drawLine(t_img *img, int x0, int y0, int x1, int y1, t_color color1, t_color color2)
{
    int steep = abs(y1 - y0) > abs(x1 - x0);

    if (steep)
    {
          int temp = x0;
        x0 = y0;
        y0 = temp;

        temp = x1;
        x1 = y1;
        y1 = temp;
    }

    if (x0 > x1)
    {
         int temp = x0;
        x0 = x1;
        x1 = temp;

        temp = y0;
        y0 = y1;
        y1 = temp;

        // Swap colors if needed
        // const t_color tempColor = color1;
        // color1 = color2;
        // color2 = tempColor;
    }

    int dx = x1 - x0, dy = y1 - y0;
    //float gradient = (dx == 0) ? 1.0 : (float)dy / dx;

    // // Handle first endpoint
    // int xend = round(x0);
    // float yend = y0 + gradient * (xend - x0);
    // float xgap = rfpart(x0 + 0.5);
    // int xpxl1 = xend, ypxl1 = ipart(yend);
    // plotHelper(ypxl1, xpxl1, rfpart(yend) * xgap);
    // plotHelper(ypxl1 + 1, xpxl1, fpart(yend) * xgap);

    // float intery = yend + gradient; // First y-intersection for the main loop

    // // Handle second endpoint
    // xend = round(x1);
    // yend = y1 + gradient * (xend - x1);
    // xgap = fpart(x1 + 0.5);
    // int xpxl2 = xend, ypxl2 = ipart(yend);
    // plotHelper(ypxl2, xpxl2, rfpart(yend) * xgap);
    // plotHelper(ypxl2 + 1, xpxl2, fpart(yend) * xgap);

    // Main loop
    // for (int x = xpxl1 + 1; x < xpxl2; x++)
    // {
    //     plotHelper(ipart(intery), x, rfpart(intery), color1, color2, img, steep);
    //     plotHelper(ipart(intery) + 1, x, fpart(intery), color1, color2, img, steep);
    //     intery += gradient;
    // }
      for (int x = x0; x <= x1; x++) {
        float t = (x - x0) / (float)dx;
        int y = y0 + t * dy;

        float brightness = rfpart(t);
        t_color interpolatedColor;
        interpolatedColor.r = lerp(color1.r, color2.r, brightness);
        interpolatedColor.g = lerp(color1.g, color2.g, brightness);
        interpolatedColor.b = lerp(color1.b, color2.b, brightness);

        plot(img, steep ? y : x, steep ? x : y, &interpolatedColor);
    }
}
