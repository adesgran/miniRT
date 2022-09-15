/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 12:36:50 by adesgran          #+#    #+#             */
/*   Updated: 2022/09/15 15:01:25 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

static int	check_shadow(t_env *env, t_light *light, t_line *ray,
t_coord *contact)
{
	t_shapes		*shapes;
	double			u;
	double			dist_light;

	shapes = env->shapes;
	dist_light = get_dist(&light->pos, contact);
	while (shapes)
	{
		u = shapes->ft_finder(shapes, ray);
		if (u > 0.0001 && u < dist_light)
			return (1);
		shapes = shapes->next;
	}
	return (0);
}

static double	get_ld(t_env *env, t_line *ray, t_line *normale)
{
	if (get_angle(&normale->dir, &ray->dir) > M_PI / 2)
		return (0);
	return (KD * (env->light->color.i
			/ pow(get_dist(&ray->pos, &env->light->pos), 2))
		* max(0, cos(get_angle(&normale->dir, &ray->dir))));
}

static double	get_ls(t_env *env, t_line *ray, t_line *normale,
t_line *bisector)
{
	return (KS * (env->light->color.i
			/ pow(get_dist(&ray->pos, &env->light->pos), 2))
		* pow(max(0, cos(get_angle(&normale->dir, &bisector->dir))), 100));
}

void	add_color(t_color *c1, double coeff, t_color *res)
{
	t_color	tmp;

	color_ratio(c1, coeff, &tmp);
	color_add(res, &tmp);
}

unsigned int	get_shape_color(t_env *env, t_line *line, t_shapes *shape)
{
	t_line	ray;
	t_line	bisector;
	t_color	res;
	t_color	tmp;
	t_light	*light;

	set_norm_dir(&shape->norm.dir, &line->dir);
	color_black(&res);
	light = env->light;
	while (light)
	{
		init_ray(light, &shape->norm, &ray);
		if (!check_shadow(env, light, &ray, &shape->norm.pos))
		{
			set_bisector(&ray, line, &bisector);
			color_sub(&light->color, &shape->color, &tmp);
			add_color(&tmp, get_ld(env, &ray, &shape->norm), &res);
			add_color(&light->color, get_ls(env, &ray, &shape->norm,
					&bisector), &res);
		}
		light = light->next;
	}
	color_sub(env->ambiant_light, &shape->color, &tmp);
	add_color(&tmp, KA * env->ambiant_light->i, &res);
	return (color_to_ui(res));
}
