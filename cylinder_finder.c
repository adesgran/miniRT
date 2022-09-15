/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_finder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 15:13:18 by adesgran          #+#    #+#             */
/*   Updated: 2022/09/15 14:59:56 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

void	cylinder_norm(t_shapes *shape, t_line *line, double t)
{
	t_cylindre	*cylindre;
	t_coord		r;
	t_coord		*va;

	cylindre = (t_cylindre *)shape->content;
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
}

double	cylinder_finder(t_shapes *shape, t_line *line)
{
	t_line		sline;
	t_cylindre	*cylindre;
	double		t;
	double		tp;

	cylindre = (t_cylindre *)shape->content;
	color_cpy(&cylindre->color, &shape->color);
	t = get_t(cylindre, line);
	if (t < 0)
		return (-1);
	coord_cpy(&sline.dir, &cylindre->dir);
	tp = check_collision(cylindre, &sline, line, t);
	return (tp);
}
