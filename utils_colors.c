#include "fdf.h"

int is_dark(t_color color)
{
	int brightness = color.r * RED_COEFFICIENT + color.g * GREEN_COEFFICIENT + color.b * BLUE_COEFFICIENT;
	return brightness < DARK_THRESHOLD;
}

void gen_gradient()
{
    do
    {
        gradients[0].r = rand() % 256;
        gradients[0].g = rand() % 256;
        gradients[0].b = rand() % 256;

        gradients[1].r = rand() % 256;
        gradients[1].g = rand() % 256;
        gradients[1].b = rand() % 256;
    } while (is_dark(gradients[0]) || is_dark(gradients[1]));
}