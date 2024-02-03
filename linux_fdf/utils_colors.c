/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vshcherb <vshcherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 03:10:30 by vshcherb          #+#    #+#             */
/*   Updated: 2024/02/03 03:10:32 by vshcherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int is_contrast(t_color color1, t_color color2)
{
    int brightness1;
    int brightness2;

    brightness1 = color1.r * RED_COEFFICIENT + color1.g * GREEN_COEFFICIENT + color1.b * BLUE_COEFFICIENT; 
    brightness2 = color2.r * RED_COEFFICIENT + color2.g * GREEN_COEFFICIENT + color2.b * BLUE_COEFFICIENT;
    return (abs(brightness1 - brightness2) > DARK_THRESHOLD);
}

t_color *gen_gradient(void)
{
    t_color *gradients;

    srand(time(NULL));
    gradients = malloc(2 * sizeof(t_color));
    if (gradients == NULL)
        return (NULL);
    do
    {
    gradients[0].r = rand() % 256;
    gradients[0].g = rand() % 256;
    gradients[0].b = rand() % 256;
    gradients[1].r = rand() % 256;
    gradients[1].g = rand() % 256;
    gradients[1].b = rand() % 256;
    } while (!is_contrast(gradients[0], gradients[1]));
    return (gradients);
}

void    print_gradient(t_color *gradient)
{
    if (gradient != NULL)
    {
        printf("Gradient 0: R - %d, G - %d, B - %d\n", gradient[0].r, gradient[0].g, gradient[0].b);
        printf("Gradient 1: R - %d, G - %d, B - %d\n", gradient[1].r, gradient[1].g, gradient[1].b);
    }
    else
        printf("Failed to generate gradient.\n");
}

// int gradient_to_int(t_color *color)
// {
//     return ((color->r << 16) | (color->g << 8) | color->b);
// }

int hex_char_to_int(char hex_char)
{
    if (hex_char >= '0' && hex_char <= '9')
        return hex_char - '0';
    else if (hex_char >= 'a' && hex_char <= 'f')
        return 10 + (hex_char - 'a');
    else if (hex_char >= 'A' && hex_char <= 'F')
        return 10 + (hex_char - 'A');
    else
        return (-1);
}

t_color hex_to_color(char *hex_string)
{
    t_color color;
    int hex_value;
    int i;

    if (hex_string[0] == '0' && (hex_string[1] == 'x' || hex_string[1] == 'X'))
        hex_string += 2;
    hex_value = 0;
    i = 0;
    while (i < 6)
    {
        int digit = hex_char_to_int(hex_string[i]);
        if (digit == -1)
        {
            color.r = color.g = color.b = 30;
            return color;
        }
        hex_value = (hex_value << 4) | digit;
        // printf("hex_value: %d\n", hex_value);
        ++i;
    }
    color.r = (hex_value >> 16) & 0xFF;
    color.g = (hex_value >> 8) & 0xFF;
    color.b = hex_value & 0xFF;
    // printf("color: %d, %d, %d\n", color.r, color.g, color.b);
    return color;
}

void    colorize_points(t_map *map)
{
    float   step;
    int     i;
    int     j;

    i = 0;
    while (i < map->num_rows)
    {
        j = 0;
        while (j < map->num_cols)
        {
            if (map->min_val == map->max_val)
                map->coords[i][j].color = map->gradient[0];
            else
            {
                step = (float)(map->coords[i][j].value - map->min_val) / (map->max_val - map->min_val);
                map->coords[i][j].color.r = map->gradient[0].r + step * (map->gradient[1].r - map->gradient[0].r);
                map->coords[i][j].color.g = map->gradient[0].g + step * (map->gradient[1].g - map->gradient[0].g);
                map->coords[i][j].color.b = map->gradient[0].b + step * (map->gradient[1].b - map->gradient[0].b);
            }
            j++;
        }
        i++;
    }
}
