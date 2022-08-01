/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_rotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 19:33:52 by adesgran          #+#    #+#             */
/*   Updated: 2022/08/01 19:36:05 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

static void	rotate_x(t_coord *p, double angle)
{
	t_coord	res;
	double	cosa;
	double	sina;

	cosa = cos(angle);
	sina = sin(angle);
	res.y = (p->y * cosa) - (p->z * sina);
	res.z = (p->y * sina) + (p->z * cosa);
	p->y = res.y;
	p->z = res.z;
}

static void	rotate_y(t_coord *p, double angle)
{
	t_coord	res;
	double	cosa;
	double	sina;

	cosa = cos(angle);
	sina = sin(angle);
	res.x = (p->x * cosa) + (p->z * sina);
	res.z = (-1 * p->x * sina) + (p->z * cosa);
	p->x = res.x;
	p->z = res.z;
}

void	matrix_rotation(t_coord *p, double ax, double ay)
{
	rotate_x(p, ax);
	rotate_y(p, ay);
}
