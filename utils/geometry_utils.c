/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 13:30:35 by adesgran          #+#    #+#             */
/*   Updated: 2022/09/04 15:40:12 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

double	get_angle(t_coord *v1, t_coord *v2)
{
	double	u;
	double	v;
	double	dir;

	dir = ((v1->x * v2->x) + (v1->y * v2->y) \
			+ (v1->z * v2->z));
	u = sqrt(pow(v1->x, 2) + pow(v1->y, 2) + pow(v1->z, 2));
	v = sqrt(pow(v2->x, 2) + pow(v2->y, 2) + pow(v2->z, 2));
	return (acos(dir / (u * v)));
}

double	get_dist(t_coord a, t_coord b)
{
	double	tmp;

	tmp = pow(a.x - b.x, 2);
	tmp += pow(a.y - b.y, 2);
	tmp += pow(a.z - b.z, 2);
	return (sqrt(tmp));
}

double	max(double a, double b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

void	vector_product(t_coord *a, t_coord *b, t_coord *res)
{
	double	coeff;
	t_line	la;
	t_line	lb;

	//printf("A\tx=%f y=%f z=%f\n", a->x, a->y, a->z);
	//printf("B\tx=%f y=%f z=%f\n", b->x, b->y, b->z);
	la.dir.x = a->x;
	la.dir.y = a->y;
	la.dir.z = a->z;
	lb.dir.x = b->x;
	lb.dir.y = b->y;
	lb.dir.z = b->z;
	coeff = sqrt(pow(a->x, 2) + pow(a->y, 2) + pow(a->z, 2));
	coeff *= sqrt(pow(b->x, 2) + pow(b->y, 2) + pow(b->z, 2));
	coeff *= sin(get_angle(&la, &lb));
	res->x = a->y * b->z - a->z * b->y;
	res->y = a->z * b->x - a->x * b->z;
	res->z = a->x * b->y - a->y * b->x;
	//printf("Res\tx=%f y=%f z=%f\n", res->x, res->y, res->z);
	//printf("Coeff = %f", coeff);
	//printf("   x = %f", res->x);
	norm_vector(res);
	//printf("   x = %f\n", res->x);
	res->x = res->x * coeff;
	res->y *= coeff;
	res->z *= coeff;
}
