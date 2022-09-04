/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 13:36:13 by adesgran          #+#    #+#             */
/*   Updated: 2022/09/02 14:36:20 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

void	color_addition(t_color *c1, t_color *c2, t_color *res)
{
	res->r = c1->r + c2->r;
	res->g = c1->g + c2->g;
	res->b = c1->b + c2->b;
	if (res->r > 255)
		res->r = 255;
	if (res->g > 255)
		res->g = 255;
	if (res->b > 255)
		res->b = 255;
}

void	color_product(t_color *c1, t_color *c2, t_color *res)
{
	res->r = (c1->r * c2->r) / 255;
	res->g = (c1->g * c2->g) / 255;
	res->b = (c1->b * c2->b) / 255;
}

void	color_ratio(t_color *c1, double ratio, t_color *res)
{
	res->r = c1->r * ratio;
	res->g = c1->g * ratio;
	res->b = c1->b * ratio;
	if (res->r > 255)
		res->r = 255;
	if (res->g > 255)
		res->g = 255;
	if (res->b > 255)
		res->b = 255;
}

unsigned int	color_to_ui(t_color color)
{
	unsigned int	res;

	res = color.r;
	res *= 256;
	res += color.g;
	res *= 256;
	res += color.b;
	return (res);
}

void	color_cpy(t_color *c1, t_color *c2)
{
	c2->r = c1->r;
	c2->g = c1->g;
	c2->b = c1->b;
	c2->i = c1->i;
}
