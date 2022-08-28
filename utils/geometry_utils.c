/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 13:30:35 by adesgran          #+#    #+#             */
/*   Updated: 2022/08/28 18:39:44 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

double	get_angle(t_line *v1, t_line *v2)
{
	double	u;
	double	v;
	double	dir;

	dir = ((v1->dir.x * v2->dir.x) + (v1->dir.y * v2->dir.y) \
			+ (v1->dir.z * v2->dir.z));
	u = sqrt(pow(v1->dir.x, 2) + pow(v1->dir.y, 2) + pow(v1->dir.z, 2));
	v = sqrt(pow(v2->dir.x, 2) + pow(v2->dir.y, 2) + pow(v2->dir.z, 2));
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

void	vector_product(t_coord a, t_coord b, t_coord *res)
{
	res->x = a.y * b.z - a.z * b.y;
	res->y = a.z * b.x - a.x * b.z;
	res->x = a.x * b.y - a.y * b.x;
}
