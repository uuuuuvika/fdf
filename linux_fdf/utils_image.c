/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_image.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vshcherb <vshcherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 03:10:34 by vshcherb          #+#    #+#             */
/*   Updated: 2024/02/03 03:10:36 by vshcherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// void	img_pix_put(t_img *img, int x, int y, int color)
// {
//     char    *pixel;
//     int		i;

//     i = img->bpp - 8;
//     pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
//     while (i >= 0)
//     {
//         /* big endian, MSB is the leftmost bit */
//         if (img->endian != 0)
//             *pixel++ = (color >> i) & 0xFF;
//         /* little endian, LSB is the leftmost bit */
//         else
//             *pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
//         i -= 8;
//     }
// }

void	img_pix_put(t_img *img, int x, int y, int color)
{
    char    *pixel;

    pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
    *(int *)pixel = color;
}


