/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_vector.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 13:08:59 by adesgran          #+#    #+#             */
/*   Updated: 2022/09/14 13:13:53 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

void	norm_vector(t_coord *v)
{
	double	tot;

	tot = sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
	if (tot == 0)
		return ;
	v->x /= tot;
	v->y /= tot;
	v->z /= tot;
}
