/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 12:36:50 by adesgran          #+#    #+#             */
/*   Updated: 2022/09/06 18:24:24 by mchassig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

static int	check_shadow(t_env *env, t_line *ray)
{
	t_shapes		*shapes;
	double			u;
	
	shapes = env->shapes;
	while (shapes)
	{
		u = shapes->ft_finder(shapes, ray);
		if (u >= 0.001)
			return (1);
		shapes = shapes->next;
	}
	return (0);
}

static double	get_difuse_light(t_env *env, t_line *ray, t_line *normale)
{
	return (KD * (env->light->color.i/pow(get_dist(ray->pos, env->light->pos), 2))
		* max(0, cos(get_angle(&normale->dir, &ray->dir))));
}

static double	get_specular_light(t_env *env, t_line *ray, t_line *normale, t_line *bisector)
{
	return (KS * (env->light->color.i/pow(get_dist(ray->pos, env->light->pos), 2))
		* pow(max(0, cos(get_angle(&normale->dir, &bisector->dir))), 100));
}

static void	init_ray(t_env *env, t_line *norm, t_line *ray)
{
	ray->pos.x = norm->pos.x;
	ray->pos.y = norm->pos.y;
	ray->pos.z = norm->pos.z;
	ray->dir.x = env->light->pos.x - ray->pos.x;
	ray->dir.y = env->light->pos.y - ray->pos.y;
	ray->dir.z = env->light->pos.z - ray->pos.z;
	norm_vector(&ray->dir);
}

unsigned int	get_shape_color(t_env *env, t_line *line, t_shapes *shape)
{
	t_line	ray;
	t_line	bisector;
	double	ld;
	double	ls;
	double	la;
	t_color	color;
	t_color	tmp;
	t_color	tmp_w;
	t_color	white;
	
	white.r = 255;
	white.g = 255;
	white.b = 255;
	la = KA * env->ambiant_light->i;
	init_ray(env, &shape->norm, &ray);
	bisector.pos.x = ray.pos.x;
	bisector.pos.y = ray.pos.y;
	bisector.pos.z = ray.pos.z;
	bisector.dir.x = (-line->dir.x + ray.dir.x) / sqrt(pow(line->dir.x, 2) + pow(ray.dir.x, 2));
	bisector.dir.y = (-line->dir.y + ray.dir.y) / sqrt(pow(line->dir.y, 2) + pow(ray.dir.y, 2));
	bisector.dir.z = (-line->dir.z + ray.dir.z) / sqrt(pow(line->dir.z, 2) + pow(ray.dir.z, 2));
	norm_vector(&bisector.dir);
	ld = 0;
	ls = 0;
	if (!check_shadow(env, &ray))
	{
		ld = get_difuse_light(env, &ray, &shape->norm);
		ls = get_specular_light(env, &ray, &shape->norm, &bisector);
	}
	color_ratio(&shape->color, ld + la, &tmp);
	color_ratio(&white, ls, &tmp_w);
	color_addition(&tmp, &tmp_w, &color);
	return (color_to_ui(color));
}
