/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_finder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 15:13:18 by adesgran          #+#    #+#             */
/*   Updated: 2022/08/28 19:30:31 by adesgran         ###   ########.fr       */
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
	t_coord		r0a1;
	t_coord		ra0;
	t_line		ra1;
	t_line		ra2;
	t_coord		va;
	t_coord		s;
	t_cylindre	*cylindre;

	cylindre = (t_cylindre *)shape->content;

	norm_vector(&line->dir);
	norm_vector(&cylindre->dir);

	ra1.pos.x = 0;
	ra1.pos.y = 0;
	ra1.pos.z = 0;
	ra1.dir.x = cylindre->pos.x - (cylindre->h / 2) * cylindre->dir.x - ra1.pos.x;
	ra1.dir.y = cylindre->pos.y - (cylindre->h / 2) * cylindre->dir.y - ra1.pos.y;
	ra1.dir.z = cylindre->pos.z - (cylindre->h / 2) * cylindre->dir.z - ra1.pos.z;
	//printf("x=%f y=%f z=%f\n", ra1.dir.x, ra1.dir.y, ra1.dir.z);

	ra2.pos.x = 0;
	ra2.pos.y = 0;
	ra2.pos.z = 0;
	ra2.dir.x = cylindre->pos.x + (cylindre->h / 2) * cylindre->dir.x - ra1.pos.x;
	ra2.dir.y = cylindre->pos.y + (cylindre->h / 2) * cylindre->dir.y - ra1.pos.y;
	ra2.dir.z = cylindre->pos.z + (cylindre->h / 2) * cylindre->dir.z - ra1.pos.z;

	s.x = ra2.dir.x - ra1.dir.x;
	s.y = ra2.dir.y - ra1.dir.y;
	s.z = ra2.dir.z - ra1.dir.z;
	norm_vector(&s);

	r0a1.x = line->pos.x - ra1.dir.x;
	r0a1.y = line->pos.y - ra1.dir.y;
	r0a1.z = line->pos.z - ra1.dir.z;

	vector_product(s, r0a1, &ra0);
	vector_product(ra0, s, &ra0);

	vector_product(s, line->dir, &va);
	vector_product(va, s, &va);

	a = pow(va.x, 2) + pow(va.y, 2) + pow(va.z, 2);
	b = 2 * (ra0.x * va.x + ra0.y * va.y + ra0.z * va.z);
	c = pow(ra0.x, 2) + pow(ra0.y, 2) +  pow(ra0.z, 2) - pow(cylindre->r, 2);
	delta = pow(b, 2) - 4 * a * c;
	if (delta < 0.001)
		return (-1);
	if (delta == 0)
		return (-b / (2 * a));
	t1 = (-b - sqrt(delta)) / (2 * a);
	t2 = (-b + sqrt(delta)) / (2 * a);
	if (t1 > t2 && t2 > 0.001)
		t = t2;
	else
		t = t1;
	r = line->pos.y + t * line->dir.y;
	if ((r >= cylindre->pos.y) && r <= cylindre->pos.y + cylindre->h)
		return (t);
	return (t);
}
