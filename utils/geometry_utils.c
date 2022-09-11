/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 13:30:35 by adesgran          #+#    #+#             */
/*   Updated: 2022/09/11 15:11:09 by adesgran         ###   ########.fr       */
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

double	get_dist(t_coord *a, t_coord *b)
{
	double	tmp;

	tmp = pow(a->x - b->x, 2);
	tmp += pow(a->y - b->y, 2);
	tmp += pow(a->z - b->z, 2);
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
	res->x = a->y * b->z - a->z * b->y;
	res->y = a->z * b->x - a->x * b->z;
	res->z = a->x * b->y - a->y * b->x;
}
