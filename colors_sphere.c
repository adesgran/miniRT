/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 13:50:43 by mchassig          #+#    #+#             */
/*   Updated: 2022/08/28 14:00:06 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

unsigned int	get_shadow(t_env *env, t_sphere *curr_sphere, t_line *ray, unsigned int *color)
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
				// color = color_product(color, 0x717171 , 0.5);
				*color = color_product(curr_sphere->color, env->ambiant_light , 0);
				return (1);
				break;
			}
		}
		shapes = shapes->next;
	}
	return (0);
}

double	get_shade(t_env *env, t_line *ray, t_line *normale)
{
	//Ld = kd (I/r^2) max(0, n · l)
	return (KD * (1/pow(get_dist(ray->pos, env->light->pos), 2)) * max(0, cos(get_angle(normale, ray))));
}

double	get_specular_shading(t_env *env, t_line *ray, t_line *normale, t_line *bisector)
{
	return (KD * (1/pow(get_dist(ray->pos, env->light->pos), 2)) * pow(max(0, cos(get_angle(normale, bisector))), 100));
}

unsigned int	get_color_sphere(t_env *env, t_sphere *curr_sphere, t_line *line, double u)
{
	t_line	ray;
	t_line	normale;
	t_line	bisector;
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
	normale.dir.z = ray.pos.z - normale.pos.z;
	norm_vector(&ray.dir);
	norm_vector(&normale.dir);
	bisector.pos.x = ray.pos.x;
	bisector.pos.y = ray.pos.y;
	bisector.pos.z = ray.pos.z;
	bisector.dir.x = (-line->dir.x + ray.dir.x) / sqrt(pow(line->dir.x, 2) + pow(ray.dir.x, 2));
	bisector.dir.y = (-line->dir.y + ray.dir.y) / sqrt(pow(line->dir.y, 2) + pow(ray.dir.y, 2));
	bisector.dir.z = (-line->dir.z + ray.dir.z) / sqrt(pow(line->dir.z, 2) + pow(ray.dir.z, 2));
	norm_vector(&bisector.dir);

	if (!get_shadow(env, curr_sphere, &ray, &color))
	{
		color = color_addition(color_product(curr_sphere->color, env->ambiant_light, 0),
			color_ratio(curr_sphere->color, get_shade(env, &ray, &normale)));
		color = color_addition(color, color_ratio(env->light->color, get_specular_shading(env, &ray, &normale, &bisector)));
	}
	//color = color_addition(color_product(curr_sphere->color, env->light->color, 0),
		//color_ratio(color, get_specular_shading(env, &ray, &normale, &bisector)));
	
	return (color);
}
