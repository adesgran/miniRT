/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_object2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 13:55:42 by adesgran          #+#    #+#             */
/*   Updated: 2022/09/15 14:52:28 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

void	set_bisector(t_line *ray, t_line *line, t_line *bisector)
{
	bisector->pos.x = ray->pos.x;
	bisector->pos.y = ray->pos.y;
	bisector->pos.z = ray->pos.z;
	bisector->dir.x = (-line->dir.x + ray->dir.x) / \
			sqrt(pow(line->dir.x, 2) + pow(ray->dir.x, 2));
	bisector->dir.y = (-line->dir.y + ray->dir.y) / \
			sqrt(pow(line->dir.y, 2) + pow(ray->dir.y, 2));
	bisector->dir.z = (-line->dir.z + ray->dir.z) / \
			sqrt(pow(line->dir.z, 2) + pow(ray->dir.z, 2));
	norm_vector(&bisector->dir);
}

void	set_norm_dir(t_coord *normdir, t_coord *linedir)
{
	if (get_angle(normdir, linedir) <= M_PI / 2)
	{
		normdir->x *= -1;
		normdir->y *= -1;
		normdir->z *= -1;
	}
}

void	init_ray(t_light *light, t_line *norm, t_line *ray)
{
	ray->pos.x = norm->pos.x;
	ray->pos.y = norm->pos.y;
	ray->pos.z = norm->pos.z;
	ray->dir.x = light->pos.x - ray->pos.x;
	ray->dir.y = light->pos.y - ray->pos.y;
	ray->dir.z = light->pos.z - ray->pos.z;
	norm_vector(&ray->dir);
}
