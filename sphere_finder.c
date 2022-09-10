/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_finder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 12:41:43 by adesgran          #+#    #+#             */
/*   Updated: 2022/09/10 16:14:10 by mchassig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

/* if res < 0 : no intersection
if res == 0 : 1 intersection (if u < 0 : sphere is behind camera)
if res > 0 : 2 intersections*/
static double	sp_get_intersection(double a, double b, double c)
{
	double	res;
	double	u;

	res = b * b - 4 * a * c;
	if (res < 0)
		u = -1;
	else if (res == 0)
		u = -b / (2 * a);
	else if (res > 0)
	{
		u = (-b - sqrt(b * b - 4 * a * c)) / (2 * a);
		if (u < 0)
			u = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);
	}
	return (u);
}

double	sphere_finder(t_shapes *shape, t_line *line)
{
	double		a;
	double		b;
	double		c;
	double		u;
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
	u = sp_get_intersection(a, b, c);
	shape->norm.pos.x = line->pos.x + u * line->dir.x;
	shape->norm.pos.y = line->pos.y + u * line->dir.y;
	shape->norm.pos.z = line->pos.z + u * line->dir.z;
	shape->norm.dir.x = shape->norm.pos.x - sphere->pos.x;
	shape->norm.dir.y = shape->norm.pos.y - sphere->pos.y;
	shape->norm.dir.z = shape->norm.pos.z - sphere->pos.z;
	return (u);
}
