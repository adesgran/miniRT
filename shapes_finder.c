/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes_finder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 13:48:57 by mchassig          #+#    #+#             */
/*   Updated: 2022/09/04 12:41:42 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

unsigned int	shapes_finder(t_env *env, t_shapes *shapes, t_line *line)
{
	double			u;
	double			min;
	unsigned int	color;
	t_shapes		*tmp;

	min = -1;
	color = 0x050515;
	while (shapes)
	{
		u = shapes->ft_finder(shapes, line);
		if (u >= 0 && (min < 0 || u < min))
		{
			min = u;
			tmp = shapes;
		}
		shapes = shapes->next;
	}
	if (min >= 0)
	{
		color = get_shape_color(env, line, tmp);
	}
	(void)tmp;
	return (color);
}
