/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes_finder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 13:48:57 by mchassig          #+#    #+#             */
/*   Updated: 2022/09/02 15:27:05 by adesgran         ###   ########.fr       */
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
	color_cpy(&sphere->color, &shape->color);
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
	color_cpy(&sphere->color, &shape->color);
	shape->norm.pos.x = line->pos.x + u * line->dir.x;
	shape->norm.pos.y = line->pos.y + u * line->dir.y;
	shape->norm.pos.z = line->pos.z + u * line->dir.z;
	shape->norm.dir.x = shape->norm.pos.x - sphere->pos.x;
	shape->norm.dir.y = shape->norm.pos.y - sphere->pos.y;
	shape->norm.dir.z = shape->norm.pos.z - sphere->pos.z;
	return (u);
}

unsigned int	shapes_finder(t_env *env, t_shapes *shapes, t_line *line)
{
	double			u;
	double			min;
	unsigned int	color;
	t_shapes		*tmp;

	min = -1;
	color = color_to_ui(env->ambiant_light);
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
