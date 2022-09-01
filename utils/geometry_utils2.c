/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 12:10:03 by adesgran          #+#    #+#             */
/*   Updated: 2022/09/01 12:11:51 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

void	coord_cpy(t_coord *a, t_coord *b)
{
	a->x = b->x;
	a->y = b->y;
	a->z = b->z;
}

void	coord_sub(t_coord *a, t_coord *b, t_coord *c)
{
	a->x = b->x - c->x;
	a->y = b->y - c->y;
	a->z = b->z - c->z;
}