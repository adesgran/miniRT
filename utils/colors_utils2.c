/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 12:23:55 by adesgran          #+#    #+#             */
/*   Updated: 2022/09/14 12:35:16 by adesgran         ###   ########.fr       */
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
