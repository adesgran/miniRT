/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 13:36:13 by adesgran          #+#    #+#             */
/*   Updated: 2022/08/21 17:38:25 by mchassig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

unsigned int	color_addition(unsigned int c1, unsigned int c2)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;

	r = (c1 / 0x010000) + (c2 / 0x010000);
	if (r > 255)
		r = 255;
	g = ((c1 % 0x010000) / 0x0100) + ((c2 % 0x010000) / 0x0100);
	if (g > 255)
		g = 255;
	b = (c1 % 0x000100) + (c2 % 0x000100);
	if (b > 255)
		b = 255;
	return (r * 0x010000 + g * 0x000100 + b);
}

unsigned int	color_product(unsigned int c1, unsigned int c2, double alpha)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
	double			cosa;

	cosa = cos(alpha);
	r = (c1 / 0x010000) * (c2 / 0x010000);
	r /= 0x0100;
	r = (unsigned int)((double)r * cosa);
	g = ((c1 % 0x010000) / 0x0100) * ((c2 % 0x010000) / 0x0100);
	g /= 0x0100;
	g = (unsigned int)((double)g * cosa);
	b = (c1 % 0x000100) * (c2 % 0x000100);
	b /= 0x0100;
	b = (unsigned int)((double)b * cosa);
	return (r * 0x010000 + g * 0x000100 + b);
}

unsigned int	color_ratio(unsigned int color, double ratio)
{
	double	r;
	double	g;
	double	b;

	r = ((double)(color / 0x010000)) * ratio;
	if (r > 255)
		r = 255;
	g = ((double)((color % 0x010000) / 0x000100)) * ratio;
	if (g > 255)
		g = 255;
	b = ((double)((color % 0x000100) / 0x000001)) * ratio;
	if (b > 255)
		b = 255;
	color = (unsigned int)r * 0x010000 + (unsigned int)g * 0x000100;
	color += (unsigned int)b;
	return (color);
}
