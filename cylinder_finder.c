/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_finder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 15:13:18 by adesgran          #+#    #+#             */
/*   Updated: 2022/09/10 17:11:34 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

double	cylinder_finder(t_shapes *shape, t_line *line)
{
	t_line		sline;
	t_coord		r;
	t_coord		*va;
	t_cylindre	*cylindre;
	double		t;
	double		tp;

	cylindre = (t_cylindre *)shape->content;
	color_cpy(&cylindre->color, &shape->color);
	t = get_t(shape, line);
	//if (t > 13)
		//printf("t = %f\n", t);
	if (t < 0)
		return (-1);
	//norm_vector(&shape->norm.dir);
	//printf("x=%f y=%f z=%f\n", shape->norm.dir.x, shape->norm.dir.y, shape->norm.dir.z);
	coord_cpy(&sline.dir, &cylindre->dir);
	tp = check_collision(cylindre, &sline, line, t);
	if (tp < 0)
		return (tp); //show a plan
	else
	{
		shape->norm.pos.x = line->pos.x + line->dir.x * t;
		shape->norm.pos.y = line->pos.y + line->dir.y * t;
		shape->norm.pos.z = line->pos.z + line->dir.z * t;
		r.x = shape->norm.pos.x - cylindre->pos.x;
		r.y = shape->norm.pos.y - cylindre->pos.y;
		r.z = shape->norm.pos.z - cylindre->pos.z;
		va = get_vector_perp(&cylindre->dir, &r);
		coord_cpy(&shape->norm.dir, va);
		norm_vector(&shape->norm.dir);
		free(va);
		return (t); //show a sphere
	}
}
