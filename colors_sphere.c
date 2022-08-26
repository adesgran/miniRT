/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 13:50:43 by mchassig          #+#    #+#             */
/*   Updated: 2022/08/26 15:11:41 by mchassig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

unsigned int	get_shadow(t_env *env, t_sphere *curr_sphere, t_line *line, double u, unsigned int color)
{
	t_line			ray;
	t_shapes		*shapes;
	double			x;
	
	ray.pos.x = line->pos.x + u * line->dir.x;
	ray.pos.y = line->pos.y + u * line->dir.y;
	ray.pos.z = line->pos.z + u * line->dir.z;
	ray.dir.x = env->light->pos.x - ray.pos.x;
	ray.dir.y = env->light->pos.y - ray.pos.y;
	ray.dir.z = env->light->pos.z - ray.pos.z;
	shapes = env->shapes;
	while (shapes)
	{
		if (shapes->content != curr_sphere)
		{
			x = shapes->ft(shapes->content, &ray);
			if (x >= 0)
			{
				color = color_product(color, 0x717171 , 0.5);
			}
		}
		// if (shapes->content != curr_sphere && shapes->type == SPHERE)
		// {
		// 	x = sphere_finder(shapes->content, &ray);
		// }
		// autes shapes
		shapes = shapes->next;
	}
	return (color);
}

double	get_shade(t_env *env, t_sphere *sphere, t_line *line, double u)
{
	t_line	normale;
	t_line	ray;
	double	kd;
	
	ray.pos.x = line->pos.x + u * line->dir.x;
	ray.pos.y = line->pos.y + u * line->dir.y;
	ray.pos.z = line->pos.z + u * line->dir.z;
	ray.dir.x = env->light->pos.x - ray.pos.x;
	ray.dir.y = env->light->pos.y - ray.pos.y;
	ray.dir.z = env->light->pos.z - ray.pos.z;

	normale.pos.x = sphere->pos.x;
	normale.pos.y = sphere->pos.y;
	normale.pos.z = sphere->pos.z;
	normale.dir.x = ray.pos.x - normale.pos.x;
	normale.dir.y = ray.pos.y - normale.pos.y;
	normale.dir.z = ray.dir.z - normale.pos.z;
	//Ld = kd (I/r^2) max(0, n · l)
	kd = 1000;
	return (kd * (1/pow(get_dist(ray.pos, env->light->pos), 2))
		* max(0, cos(get_angle(&normale, &ray))));
}