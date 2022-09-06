/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_finder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 15:13:18 by adesgran          #+#    #+#             */
/*   Updated: 2022/09/06 15:47:02 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

double	cylinder_finder(t_shapes *shape, t_line *line)
{
	t_line		sline;
	t_cylindre	*cylindre;
	double		t;
	double		tp;

	cylindre = (t_cylindre *)shape->content;
	color_cpy(&cylindre->color, &shape->color);
	t = get_t(shape, line);
	if (t < 0)
		return (-1);
	shape->norm.dir.x *= 1;
	shape->norm.dir.y *= 1;
	shape->norm.dir.z *= 1;
	norm_vector(&shape->norm.dir);
	//printf("x=%f y=%f z=%f\n", shape->norm.dir.x, shape->norm.dir.y, shape->norm.dir.z);
	coord_cpy(&sline.dir, &cylindre->dir);
	tp = check_collision(cylindre, &sline, line, t);
	if (tp < 0)
		return (tp); //show a plan
	else
	{
		shape->norm.pos.x = cylindre->pos.x - cylindre->h * cylindre->dir.x / 2 + t * cylindre->dir.x - shape->norm.dir.x * cylindre->r;
		shape->norm.pos.y = cylindre->pos.y - cylindre->h * cylindre->dir.y / 2 + t * cylindre->dir.y - shape->norm.dir.y * cylindre->r;
		shape->norm.pos.z = cylindre->pos.z - cylindre->h * cylindre->dir.z / 2 + t * cylindre->dir.z - shape->norm.dir.z * cylindre->r;
		return (tp); //show a sphere
	}
}
