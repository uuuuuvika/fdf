/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_clrs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vshcherb <vshcherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 03:10:30 by vshcherb          #+#    #+#             */
/*   Updated: 2024/02/04 19:13:23 by vshcherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incl/fdf.h"

int	is_contrast(t_clr clr1, t_clr clr2)
{
	int	brightness1;
	int	brightness2;

	brightness1 = clr1.r * RED_COEFFICIENT + clr1.g 
		* GREEN_COEFFICIENT + clr1.b * BLUE_COEFFICIENT;
	brightness2 = clr2.r * RED_COEFFICIENT + clr2.g 
		* GREEN_COEFFICIENT + clr2.b * BLUE_COEFFICIENT;
	return (abs(brightness1 - brightness2) > DARK_THRESHOLD);
}

t_clr	*gen_gr(void)
{
	t_clr	*grs;

	srand(time(NULL));
	grs = malloc(2 * sizeof(t_clr));
	if (grs == NULL)
		return (NULL);
	grs[0].r = rand() % 256;
	grs[0].g = rand() % 256;
	grs[0].b = rand() % 256;
	grs[1].r = rand() % 256;
	grs[1].g = rand() % 256;
	grs[1].b = rand() % 256;
	while (!is_contrast(grs[0], grs[1]))
	{
		grs[0].r = rand() % 256;
		grs[0].g = rand() % 256;
		grs[0].b = rand() % 256;
		grs[1].r = rand() % 256;
		grs[1].g = rand() % 256;
		grs[1].b = rand() % 256;
	}
	return (grs);
}

int	hex_char_to_int(char hex_char)
{
	if (hex_char >= '0' && hex_char <= '9')
		return (hex_char - '0');
	else if (hex_char >= 'a' && hex_char <= 'f')
		return (10 + (hex_char - 'a'));
	else if (hex_char >= 'A' && hex_char <= 'F')
		return (10 + (hex_char - 'A'));
	else
		return (-1);
}

t_clr	hex_to_clr(char *hex_string)
{
	t_clr	clr;
	int		hex_value;
	int		i;
	int		digit;

	if (hex_string[0] == '0' && (hex_string[1] == 'x' || hex_string[1] == 'X'))
		hex_string += 2;
	hex_value = 0;
	i = 0;
	while (i < 6)
	{
		digit = hex_char_to_int(hex_string[i]);
		if (digit < 0)
			digit = 0;
		hex_value = (hex_value << 4) | digit;
		++i;
	}
	clr.r = (hex_value >> 16) & 0xFF;
	clr.g = (hex_value >> 8) & 0xFF;
	clr.b = hex_value & 0xFF;
	return (clr);
}
