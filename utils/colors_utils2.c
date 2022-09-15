/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 12:23:55 by adesgran          #+#    #+#             */
/*   Updated: 2022/09/15 14:23:13 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

void	color_add(t_color *res, t_color *to_add)
{
	res->r += to_add->r;
	res->g += to_add->g;
	res->b += to_add->b;
	if (res->r > 255)
		res->r = 255;
	if (res->g > 255)
		res->g = 255;
	if (res->b > 255)
		res->b = 255;
}

void	color_sub(t_color *c1, t_color *c2, t_color *res)
{
	res->r = min(c1->r, c2->r);
	res->g = min(c1->g, c2->g);
	res->b = min(c1->b, c2->b);
}

void	color_black(t_color *c)
{
	c->r = 0;
	c->g = 0;
	c->b = 0;
	c->i = 0;
}
