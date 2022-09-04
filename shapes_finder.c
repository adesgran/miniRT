/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes_finder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 13:48:57 by mchassig          #+#    #+#             */
/*   Updated: 2022/09/04 17:57:56 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

double	sphere_finder(t_shapes *shape, t_line *line)
{
	double	a;
	double	b;
	double	c;
	double	res;
	double	u;
	t_sphere	*sphere;

	sphere = (t_sphere *)shape->content;
	a = pow(line->dir.x, 2) + pow(line->dir.y, 2) + pow(line->dir.z, 2);
	b = 2 * (line->dir.x * (line->pos.x - sphere->pos.x) + line->dir.y
		* (line->pos.y - sphere->pos.y) + line->dir.z
		* (line->pos.z - sphere->pos.z));
	c = pow(sphere->pos.x, 2) + pow(sphere->pos.y, 2) + pow(sphere->pos.z, 2)
		+ pow(line->pos.x, 2) + pow(line->pos.y, 2) + pow(line->pos.z, 2) - 2.0
		* (sphere->pos.x * line->pos.x + sphere->pos.y * line->pos.y
		+ sphere->pos.z * line->pos.z) - sphere->r * sphere->r;
	res = b * b - 4 * a * c;
	if (res < 0) // no intersection
		u = -1;
	else if (res == 0) // 1 intersection at u = -b/2a (if u < 0 : sphere is behind camera)
		u = -b / (2 * a);
	else if (res > 0) // 2 intersections
	{
		u = (-b - sqrt(b * b - 4 * a * c)) / (2 * a);
		if (u < 0)
			u = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);
	}
	shape->norm.pos.x = line->pos.x + u * line->dir.x;
	shape->norm.pos.y = line->pos.y + u * line->dir.y;
	shape->norm.pos.z = line->pos.z + u * line->dir.z;
	shape->norm.dir.x = shape->norm.pos.x - sphere->pos.x;
	shape->norm.dir.y = shape->norm.pos.y - sphere->pos.y;
	shape->norm.dir.z = shape->norm.pos.z - sphere->pos.z;
	return (u);
}

double	plan_finder(t_shapes *shape, t_line *line)
{
	t_plan	*plan;
	double	u;
	double	d;
	
	norm_vector(&line->dir);
	plan = (t_plan *)shape->content;
	if ((get_angle(&line->dir, &plan->dir) - M_PI / 2) < 0.001)
		return (-1);
	d = - (plan->dir.x * plan->pos.x + plan->dir.y * plan->pos.y + plan->dir.z * plan->pos.z);
	u = - (line->pos.x * plan->dir.x + line->pos.y * plan->dir.y + line->pos.z * plan->dir.z + d);
	u /= plan->dir.x * line->dir.x + plan->dir.y * line->dir.y + plan->dir.z * line->dir.z;
	if (u < 0)
		return (-1);
	shape->norm.pos.x = line->pos.x + u * line->dir.x;
	shape->norm.pos.y = line->pos.y + u * line->dir.y;
	shape->norm.pos.z = line->pos.z + u * line->dir.z;
	shape->norm.dir.x = plan->dir.x;
	shape->norm.dir.y = plan->dir.y;
	shape->norm.dir.z = plan->dir.z;
	return (u);
}

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
	return (color);
}
