/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_finder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 15:13:18 by adesgran          #+#    #+#             */
/*   Updated: 2022/08/28 17:15:04 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

double	cylinder_finder(t_shapes *shape, t_line *line)
{
	double		a;
	double		b;
	double		c;
	double		delta;
	double		t1;
	double		t2;
	double		t;
	double		r;
	t_line		ra0;
	t_line		ra1;
	t_line		ra2;
	t_coord		s;
	t_cylindre	*cylindre;

	cylindre = (t_cylindre *)shape->content;

	norm_vector(&cylindre->dir);

	ra1.pos.x = line->pos.x;
	ra1.pos.y = line->pos.y;
	ra1.pos.z = line->pos.z;
	ra1.dir.x = cylindre->pos.x + (cylindre->h / 2) * cylindre->dir.x - ra1.pos.x;
	ra1.dir.y = cylindre->pos.y + (cylindre->h / 2) * cylindre->dir.y - ra1.pos.y;
	ra1.dir.z = cylindre->pos.z + (cylindre->h / 2) * cylindre->dir.z - ra1.pos.z;

	ra2.pos.x = line->pos.x;
	ra2.pos.y = line->pos.y;
	ra2.pos.z = line->pos.z;
	ra2.dir.x = cylindre->pos.x - (cylindre->h / 2) * cylindre->dir.x - ra1.pos.x;
	ra2.dir.y = cylindre->pos.y - (cylindre->h / 2) * cylindre->dir.y - ra1.pos.y;
	ra2.dir.z = cylindre->pos.z - (cylindre->h / 2) * cylindre->dir.z - ra1.pos.z;

	(void)s;
	(void)ra2;
	(void)ra0;

	a = pow(line->dir.x, 2) + pow(line->dir.y, 2) + pow(line->dir.z, 2);
	b = 2 * (line->dir.x * (line->pos.x - cylindre->pos.x) + (line->dir.y * (line->pos.y - cylindre->pos.y)) + (line->dir.z * (line->pos.z - cylindre->pos.z)));
	c = pow(line->pos.x - cylindre->pos.x, 2) + pow(line->pos.y - cylindre->pos.y, 2) +  pow(line->pos.z - cylindre->pos.z, 2) - pow(cylindre->r, 2);
	delta = pow(b, 2) - 4 * a * c;
	if (delta < 0)
		return (delta);
	if (delta == 0)
		return (-b);
	t1 = (-b - sqrt(delta)) / (2 * a);
	t2 = (-b + sqrt(delta)) / (2 * a);
	if (t1 > t2)
		t = t2;
	else
		t = t1;
	r = line->pos.y + t * line->dir.y;
	if ((r >= cylindre->pos.y) && r <= cylindre->pos.y + cylindre->h)
		return (t);
	return (-1);
}
