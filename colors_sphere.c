/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 13:50:43 by mchassig          #+#    #+#             */
/*   Updated: 2022/08/27 18:59:09 by mchassig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

unsigned int	get_shadow(t_env *env, t_sphere *curr_sphere, t_line *ray, unsigned int color)
{
	t_shapes		*shapes;
	double			x;
	
	shapes = env->shapes;
	while (shapes)
	{
		if (shapes->content != curr_sphere)
		{
			x = shapes->ft_finder(shapes->content, ray);
			if (x >= 0)
			{
				color = color_product(color, 0x717171 , 0.5);
			}
		}
		shapes = shapes->next;
	}
	return (color);
}

double	get_shade(t_env *env, t_line *ray, t_line *normale)
{
	//Ld = kd (I/r^2) max(0, n · l)
	return (1000 * (1/pow(get_dist(ray->pos, env->light->pos), 2))
		* max(0, cos(get_angle(normale, ray))));
}

unsigned int	get_color_sphere(t_env *env, t_sphere *curr_sphere, t_line *line, double u)
{
	t_line	ray;
	t_line	normale;
	unsigned int	color;
	
	ray.pos.x = line->pos.x + u * line->dir.x;
	ray.pos.y = line->pos.y + u * line->dir.y;
	ray.pos.z = line->pos.z + u * line->dir.z;
	ray.dir.x = env->light->pos.x - ray.pos.x;
	ray.dir.y = env->light->pos.y - ray.pos.y;
	ray.dir.z = env->light->pos.z - ray.pos.z;
	normale.pos.x = curr_sphere->pos.x;
	normale.pos.y = curr_sphere->pos.y;
	normale.pos.z = curr_sphere->pos.z;
	normale.dir.x = ray.pos.x - normale.pos.x;
	normale.dir.y = ray.pos.y - normale.pos.y;
	normale.dir.z = ray.dir.z - normale.pos.z;
	color = color_addition(color_product(curr_sphere->color, env->ambiant_light, 0),
			color_ratio(curr_sphere->color, get_shade(env, &ray, &normale)));
	color = get_shadow(env, curr_sphere, &ray, color);
	return (color);
}