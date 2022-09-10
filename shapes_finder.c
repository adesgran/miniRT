/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes_finder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 13:48:57 by mchassig          #+#    #+#             */
/*   Updated: 2022/09/10 18:01:53 by mchassig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

double	plan_finder(t_shapes *shape, t_line *line)
{
	t_plan	*plan;
	double	u;
	double	d;
	double	a;
	double	coef;
	
	norm_vector(&line->dir);
	plan = (t_plan *)shape->content;
	a = get_angle(&line->dir, &plan->dir);
	if (fabs(a - M_PI / 2) < 0.001)
		return (-1);
	if (fabs(a) < 3 * M_PI / 2)
		coef = -1;
	else
		coef = 1;
	d = - (plan->dir.x * plan->pos.x + plan->dir.y * plan->pos.y + plan->dir.z * plan->pos.z);
	u = - (line->pos.x * plan->dir.x + line->pos.y * plan->dir.y + line->pos.z * plan->dir.z + d);
	u /= plan->dir.x * line->dir.x + plan->dir.y * line->dir.y + plan->dir.z * line->dir.z;
	if (u < 0)
		return (-1);
	shape->norm.pos.x = line->pos.x + u * line->dir.x;
	shape->norm.pos.y = line->pos.y + u * line->dir.y;
	shape->norm.pos.z = line->pos.z + u * line->dir.z;
	shape->norm.dir.x = plan->dir.x * coef;
	shape->norm.dir.y = plan->dir.y * coef;
	shape->norm.dir.z = plan->dir.z * coef;
	return (u);
}

unsigned int	shapes_finder(t_env *env, t_shapes *shapes, t_line *line)
{
	double			u;
	double			min;
	unsigned int	color;
	t_shapes		*tmp;

	norm_vector(&line->dir);
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
