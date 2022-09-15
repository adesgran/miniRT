/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 14:20:05 by adesgran          #+#    #+#             */
/*   Updated: 2022/09/15 13:24:50 by mchassig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

static double	t_calc(t_coord *va, t_coord *ra0, t_cylindre *cy)
{
	float		a;
	float		b;
	float		c;
	float		delta;
	double		t1;
	double		t2;
	double		t;

	a = pow(va->x, 2.0) + pow(va->y, 2.0) + pow(va->z, 2.0);
	b = 2.0 * (ra0->x * va->x + ra0->y * va->y + ra0->z * va->z);
	c = pow(ra0->x, 2.0) + pow(ra0->y, 2.0) +  pow(ra0->z, 2.0) - pow(cy->r, 2.0);
	delta = pow(b, 2.0) - 4.0 * a * c;
	if (delta <= 0.00000)
		return (-1);
	t1 = (-b - sqrt(delta)) / (2.0 * a);
	t2 = (-b + sqrt(delta)) / (2.0 * a);
	if ((t1 > t2 && t2 >= 0.00000) || t1 <= 0.0000)
		t = t2;
	else
		t = t1;
	return (t);
}

double	get_t(t_shapes *shape, t_line *line)
{
	t_coord		ra1;
	t_coord		s;
	t_coord		r0a1;
	t_coord		*ra0;
	t_coord		*va;
	t_cylindre	*cylindre;
	double		t;

	cylindre = (t_cylindre *)shape->content;
	ra1.x = cylindre->pos.x - (cylindre->h / 2.0) * cylindre->dir.x;
	ra1.y = cylindre->pos.y - (cylindre->h / 2.0) * cylindre->dir.y;
	ra1.z = cylindre->pos.z - (cylindre->h / 2.0) * cylindre->dir.z;
	coord_cpy(&s, &cylindre->dir);
	norm_vector(&s);
	r0a1.x = line->pos.x - ra1.x;
	r0a1.y = line->pos.y - ra1.y;
	r0a1.z = line->pos.z - ra1.z;
	ra0 = get_vector_perp(&s, &r0a1);
	norm_vector(&line->dir);
	va = get_vector_perp(&s, &line->dir);
	if (!ra0 || !va)
		return (free(ra0), free(va), -1);
	t = t_calc(va, ra0, cylindre);
	return (free(va), free(ra0), t);
}

double	check_collision(t_cylindre *cy, t_line *sline, t_line *line, double t)
{
	t_coord	ra1;
	t_coord	ra2;

	ra1.x = line->pos.x + t * line->dir.x;
	ra1.y = line->pos.y + t * line->dir.y;
	ra1.z = line->pos.z + t * line->dir.z;
	ra2.x = line->pos.x + t * line->dir.x;
	ra2.y = line->pos.y + t * line->dir.y;
	ra2.z = line->pos.z + t * line->dir.z;
	ra1.x -= cy->pos.x - (cy->h / 2) * cy->dir.x;
	ra1.y -= cy->pos.y - (cy->h / 2) * cy->dir.y;
	ra1.z -= cy->pos.z - (cy->h / 2) * cy->dir.z;
	ra2.x -= cy->pos.x + (cy->h / 2) * cy->dir.x;
	ra2.y -= cy->pos.y + (cy->h / 2) * cy->dir.y;
	ra2.z -= cy->pos.z + (cy->h / 2) * cy->dir.z;
	norm_vector(&ra1);
	norm_vector(&ra2);
	if (cos(get_angle(&ra1, &sline->dir)) > 0 && cos(get_angle(&ra2, &sline->dir)) < 0)
		return (t); //Read as a sphere
	else
		return (-1); //Read as a plan
}
