#include "fdf.h"

#define KEY_ESC 53

Color gradientColors[2];
double rotationAngle = 0.0;

int handle_keypress(int key, t_data *data)
{
	if (key == KEY_ESC)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
	}
	exit(0);
}

// int draw_square(t_data *data)
// {
//     int side_length = 100;
//     int x = WIDTH / 2 - side_length / 2;
//     int y = HEIGHT / 2 - side_length / 2;

//     if (data->win_ptr != NULL)
//     {
//         for (int i = x; i < x + side_length; i++)
//         {
//             for (int j = y; j < y + side_length; j++)
//             {
//                 // Calculate the gradient color based on the position within the square
//                 int red = 0;
//                 int green = (i - x) * 255 / side_length;
//                 int blue = (j - y) * 255 / side_length;

//                 // Combine the color components
//                 int color = (red << 16) | (green << 8) | blue;

//                 mlx_pixel_put(data->mlx_ptr, data->win_ptr, i, j, color);
//             }
//         }
//     }

//     return (0);
// }

int isDarkColor(Color color)
{
	int brightness = color.r * RED_COEFFICIENT + color.g * GREEN_COEFFICIENT + color.b * BLUE_COEFFICIENT;
	return brightness < DARK_THRESHOLD;
}

void generateGradientPalette()
{
	for (int i = 0; i < 2; i++)
	{
		do
		{
			gradientColors[i].r = rand() % 256;
			gradientColors[i].g = rand() % 256;
			gradientColors[i].b = rand() % 256;
		} while (isDarkColor(gradientColors[i]));
	}
}

int draw_square(t_data *data)
{
	int side_length = 200;
	int x = WIDTH / 2 - side_length / 2;
	int y = HEIGHT / 2 - side_length / 2;

	if (data->win_ptr != NULL)
	{
		rotationAngle += 0.001;
		for (int i = x; i < x + side_length; i++)
		{
			for (int j = y; j < y + side_length; j++)
			{
				int rotatedX = (i - WIDTH / 2) * cos(rotationAngle) - (j - HEIGHT / 2) * sin(rotationAngle) + WIDTH / 2;
				int rotatedY = (i - WIDTH / 2) * sin(rotationAngle) + (j - HEIGHT / 2) * cos(rotationAngle) + HEIGHT / 2;
				int red = gradientColors[0].r + (rotatedX - x) * (gradientColors[1].r - gradientColors[0].r) / side_length;
				int green = gradientColors[0].g + (rotatedX - x) * (gradientColors[1].g - gradientColors[0].g) / side_length;
				int blue = gradientColors[0].b + (rotatedX - x) * (gradientColors[1].b - gradientColors[0].b) / side_length;

				// Combine the color components
				int color = (red << 16) | (green << 8) | blue;

				mlx_pixel_put(data->mlx_ptr, data->win_ptr, rotatedX, rotatedY, color);
			}
		}
	}

	return (0);
}

int main(void)
{
	srand(time(NULL));

	t_data data;

	data.mlx_ptr = mlx_init();

	if (data.mlx_ptr == NULL)
		return (MLX_ERROR);

	data.win_ptr = mlx_new_window(data.mlx_ptr, WIDTH, HEIGHT, "Gradient Square");

	if (data.win_ptr == NULL)
	{
		free(data.win_ptr);
		return (MLX_ERROR);
	}

	generateGradientPalette();
	mlx_loop_hook(data.mlx_ptr, &draw_square, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
	mlx_loop(data.mlx_ptr);

	return 0;
}
