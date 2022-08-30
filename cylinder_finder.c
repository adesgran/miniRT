/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_finder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 15:13:18 by adesgran          #+#    #+#             */
/*   Updated: 2022/08/30 13:23:47 by adesgran         ###   ########.fr       */
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
	t_line		sline;
	t_coord		tmp;
	t_cylindre	*cylindre;
	t_line		raya1;
	t_line		raya2;

	cylindre = (t_cylindre *)shape->content;

	norm_vector(&line->dir);
	norm_vector(&cylindre->dir);

	//printf("CY x=%f y=%f z=%f\n", cylindre->dir.x, cylindre->dir.y, cylindre->dir.z);
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

	s.x = cylindre->dir.x;
	s.y = cylindre->dir.y;
	s.z = cylindre->dir.z;
	norm_vector(&s);

	r0a1.x = line->pos.x - ra1.dir.x;
	r0a1.y = line->pos.y - ra1.dir.y;
	r0a1.z = line->pos.z - ra1.dir.z;

	ra0.x = 0;
	ra0.y = 0;
	ra0.z = 0;
	//printf("x=%f y=%f z=%f\n", r0a1.x, r0a1.y, r0a1.z);

	vector_product(&s, &r0a1, &tmp);
	//printf("x=%f y=%f z=%f\n", tmp.x, tmp.y, tmp.z);
	vector_product(&tmp, &s, &ra0);
	//printf("x=%f y=%f z=%f\n", ra0.x, ra0.y, ra0.z);

	va.x = 0;
	va.y = 0;
	va.z = 0;

	(void)r0a1;
	(void)ra2;
	vector_product(&s, &line->dir, &tmp);
	vector_product(&tmp, &s, &va);
	//printf("x=%f y=%f z=%f\n", va.x, va.y, va.z);
	

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
	raya1.dir.x = line->pos.x + t * line->dir.x - ra1.dir.x;
	raya1.dir.y = line->pos.y + t * line->dir.y - ra1.dir.y;
	raya1.dir.z = line->pos.z + t * line->dir.z - ra1.dir.z;
	raya2.dir.x = line->pos.x + t * line->dir.x - ra2.dir.x;
	raya2.dir.y = line->pos.y + t * line->dir.y - ra2.dir.y;
	raya2.dir.z = line->pos.z + t * line->dir.z - ra2.dir.z;
	sline.dir.x = s.x;
	sline.dir.y = s.y;
	sline.dir.z = s.z;
	norm_vector(&raya1.dir);
	norm_vector(&raya2.dir);
	//if ((r >= cylindre->pos.y) && r <= cylindre->pos.y + cylindre->h)
	//printf("%f %f\n",cos(get_angle(&raya1, &sline)), cos(get_angle(&raya2, &sline)));
	if (cos(get_angle(&raya1, &sline)) > 0 && cos(get_angle(&raya2, &sline)) < 0)
		return (t);
	else
		return (-1);
	(void)r;
	return (t);
}
