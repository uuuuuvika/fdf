#include "fdf.h"

int isDarkColor(t_color color)
{
	int brightness = color.r * RED_COEFFICIENT + color.g * GREEN_COEFFICIENT + color.b * BLUE_COEFFICIENT;
	return brightness < DARK_THRESHOLD;
}

void generateGradientPalette()
{
    do
    {
        gradientColors[0].r = rand() % 256;
        gradientColors[0].g = rand() % 256;
        gradientColors[0].b = rand() % 256;

        gradientColors[1].r = rand() % 256;
        gradientColors[1].g = rand() % 256;
        gradientColors[1].b = rand() % 256;
    } while (isDarkColor(gradientColors[0]) || isDarkColor(gradientColors[1]));
}