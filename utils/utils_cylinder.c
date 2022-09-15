/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 14:20:05 by adesgran          #+#    #+#             */
/*   Updated: 2022/09/15 14:58:59 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

static double	t_cmp(double t1, double t2)
{
	if ((t1 > t2 && t2 >= 0.00000) || t1 <= 0.0000)
		return (t2);
	else
		return (t1);
}

static double	t_calc(t_coord *va, t_coord *ra0, t_cylindre *cy)
{
	float		a;
	float		b;
	float		c;
	float		delta;

	a = pow(va->x, 2.0) + pow(va->y, 2.0) + pow(va->z, 2.0);
	b = 2.0 * (ra0->x * va->x + ra0->y * va->y + ra0->z * va->z);
	c = pow(ra0->x, 2.0) + pow(ra0->y, 2.0) + pow(ra0->z, 2.0)
		- pow(cy->r, 2.0);
	delta = pow(b, 2.0) - 4.0 * a * c;
	if (delta <= 0.00000)
		return (-1);
	return (t_cmp((-b - sqrt(delta)) / (2.0 * a),
			(-b + sqrt(delta)) / (2.0 * a)));
}

double	get_t(t_cylindre *cylindre, t_line *line)
{
	t_coord		ra1;
	t_coord		r0a1;
	t_coord		*ra0;
	t_coord		*va;
	double		t;

	ra1.x = cylindre->pos.x - (cylindre->h / 2.0) * cylindre->dir.x;
	ra1.y = cylindre->pos.y - (cylindre->h / 2.0) * cylindre->dir.y;
	ra1.z = cylindre->pos.z - (cylindre->h / 2.0) * cylindre->dir.z;
	r0a1.x = line->pos.x - ra1.x;
	r0a1.y = line->pos.y - ra1.y;
	r0a1.z = line->pos.z - ra1.z;
	ra0 = get_vector_perp(&cylindre->dir, &r0a1);
	norm_vector(&line->dir);
	va = get_vector_perp(&cylindre->dir, &line->dir);
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
	if (cos(get_angle(&ra1, &sline->dir)) > 0
		&& cos(get_angle(&ra2, &sline->dir)) < 0)
		return (t);
	else
		return (-1);
}
