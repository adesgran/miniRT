/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 12:36:50 by adesgran          #+#    #+#             */
/*   Updated: 2022/09/14 13:14:38 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

static int	check_shadow(t_env *env, t_light *light, t_line *ray, t_coord *contact)
{
	t_shapes		*shapes;
	double			u;
	double			dist_light;

	shapes = env->shapes;
	//(void)ray;
	dist_light = get_dist(&light->pos, contact);
	while (shapes)
	{
		u = shapes->ft_finder(shapes, ray);
		//u = -2;
		if (u > 0.0001 && u <  dist_light)
			return (1);
		shapes = shapes->next;
	}
	return (0);
}

static double	get_difuse_light(t_env *env, t_line *ray, t_line *normale)
{
	//printf("angle2 = %f\n", get_angle(&normale->dir, &ray->dir));
	if (get_angle(&normale->dir, &ray->dir) > M_PI / 2)
		return (0);
	return (KD * (env->light->color.i/pow(get_dist(&ray->pos, &env->light->pos), 2))
			* max(0, cos(get_angle(&normale->dir, &ray->dir))));
}

static double	get_specular_light(t_env *env, t_line *ray, t_line *normale, t_line *bisector)
{
	return (KS * (env->light->color.i/pow(get_dist(&ray->pos, &env->light->pos), 2))
			* pow(max(0, cos(get_angle(&normale->dir, &bisector->dir))), 100));
}

static void	init_ray(t_light *light, t_line *norm, t_line *ray)
{
	ray->pos.x = norm->pos.x;
	ray->pos.y = norm->pos.y;
	ray->pos.z = norm->pos.z;
	ray->dir.x = light->pos.x - ray->pos.x;
	ray->dir.y = light->pos.y - ray->pos.y;
	ray->dir.z = light->pos.z - ray->pos.z;
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
	t_color	tmp2;
	t_light	*light;

	//if (0)
	norm_vector(&shape->norm.dir);
	//printf("x=%f y=%f z=%f\n", line->dir.x, line->dir.y, line->dir.z);
	//printf("angle1 = %f\n", get_angle(&shape->norm.dir, &line->dir));
	if (get_angle(&shape->norm.dir, &line->dir) <= M_PI / 2)
	{
		shape->norm.dir.x *= -1;
		shape->norm.dir.y *= -1;
		//printf("1%f\n", shape->norm.dir.z);
		shape->norm.dir.z *= -1;
		//printf("2%f\n", shape->norm.dir.z);
	}
	la = KA * env->ambiant_light->i;
	ld = 0;
	ls = 0;
	color.r = 0;
	color.g = 0;
	color.b = 0;
	light = env->light;
	while (light)
	{
		init_ray(light, &shape->norm, &ray);
		if (!check_shadow(env, light, &ray, &shape->norm.pos))
		{
			bisector.pos.x = ray.pos.x;
			bisector.pos.y = ray.pos.y;
			bisector.pos.z = ray.pos.z;
			bisector.dir.x = (-line->dir.x + ray.dir.x) / sqrt(pow(line->dir.x, 2) + pow(ray.dir.x, 2));
			bisector.dir.y = (-line->dir.y + ray.dir.y) / sqrt(pow(line->dir.y, 2) + pow(ray.dir.y, 2));
			bisector.dir.z = (-line->dir.z + ray.dir.z) / sqrt(pow(line->dir.z, 2) + pow(ray.dir.z, 2));
			norm_vector(&bisector.dir);
			ld = get_difuse_light(env, &ray, &shape->norm);
			ls = get_specular_light(env, &ray, &shape->norm, &bisector);
			color_sub(&light->color, &shape->color, &tmp2);
			color_ratio(&tmp2, ld, &tmp);
			color_add(&color, &tmp);
			color_ratio(&light->color, ls, &tmp);
			color_add(&color, &tmp);
		}
		light = light->next;
	}
	color_sub(env->ambiant_light, &shape->color, &tmp2);
	color_ratio(&tmp2, la, &tmp);
	color_add(&color, &tmp);
	return (color_to_ui(color));
}
