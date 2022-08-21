/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 01:56:43 by adesgran          #+#    #+#             */
/*   Updated: 2022/08/21 16:03:29 by mchassig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

int	get_key(int keycode, t_vars *vars)
{
	if (keycode == KEY_ESCAPE)
	{
		mlx_loop_end(vars->mlx);
		return (0);
	}
	printf("\033[0;33mKEYCODE = %d\033[0m\n", keycode);
	return (0);
}

t_line	*linecpy(t_camera *camera, double ax, double ay)
{
	t_line	*line;

	line = malloc(sizeof(t_line));
	if (!line)
		return (NULL);
	line->pos.x = camera->pos.x;
	line->pos.y = camera->pos.y;
	line->pos.z = camera->pos.z;
	line->dir.x = camera->dir.x;
	line->dir.y = camera->dir.y;
	line->dir.z = camera->dir.z;
	matrix_rotation(&(line->dir), ax, ay);
	return (line);
}

double	sphere_finder(t_sphere *sphere, t_line *line)
{
	double	a;
	double	b;
	double	c;
	double	res;
	double	u;

	a = pow(line->dir.x, 2) + pow(line->dir.y, 2) + pow(line->dir.z, 2);
	b = 2 * (line->dir.x * (line->pos.x - sphere->pos.x) + line->dir.y
			* (line->pos.y - sphere->pos.y) + line->dir.z
			* (line->pos.z - sphere->pos.z));
	c = pow(sphere->pos.x, 2) + pow(sphere->pos.y, 2) + pow(sphere->pos.z, 2)
		+ pow(line->pos.x, 2) + pow(line->pos.y, 2) + pow(line->pos.z, 2) - 2.0
		* (sphere->pos.x * line->pos.x + sphere->pos.y * line->pos.y
			+ sphere->pos.z * line->pos.z) - sphere->r * sphere->r;
	res = b * b - 4 * a * c;
	if (res < 0) // no intersection
		u = -1;
	else if (res == 0) // 1 intersection at u = -b/2a (if u < 0 : sphere is behind camera)
		u = -b / (2 * a);
	else if (res > 0) // 2 intersections
	{
		u = (-b - sqrt(b * b - 4 * a * c)) / (2 * a);
		if (u < 0)
			u = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);
	}
	return (u);
}

unsigned int	get_shadow(t_env *env, t_sphere *sphere, t_line *line, double u)
{
	t_line		ray;
	t_shapes	*shapes;
	unsigned int	color;
	double			x;
	
	ray.pos.x = line->pos.x + u * line->dir.x;
	ray.pos.y = line->pos.y + u * line->dir.y;
	ray.pos.z = line->pos.z + u * line->dir.z;
	ray.dir.x = ray.pos.x - env->light->pos.x;
	ray.dir.y = ray.pos.y - env->light->pos.y;
	ray.dir.z = ray.pos.z - env->light->pos.z;
	shapes = env->shapes;
	color = 0x00ff00;
	while (shapes)
	{
		if (shapes->content != sphere && shapes->type == SPHERE)
		{
			x = sphere_finder((t_sphere *)shapes->content, &ray);
			if (x >= 0)
			{
				color = env->ambiant_light;
			}
		}
		shapes = shapes->next;
	}
	(void)sphere;
	return (color);
}

// unsigned int	get_shade(t_env *env, t_sphere *sphere, t_line *line, double u)
// {
// 	t_line	normale;
// 	t_line	ray;
	
// 	ray.pos.x = line->pos.x + u * line->dir.x;
// 	ray.pos.y = line->pos.y + u * line->dir.y;
// 	ray.pos.z = line->pos.z + u * line->dir.z;
// 	ray.dir.x = ray.pos.x - env->light->pos.x;
// 	ray.dir.y = ray.pos.y - env->light->pos.y;
// 	ray.dir.z = ray.pos.z - env->light->pos.z;

// 	normale.pos.x = sphere->pos.x;
// 	normale.pos.y = sphere->pos.y;
// 	normale.pos.z = sphere->pos.z;
// 	normale.dir.x = line->pos.x + u * line->dir.x;
// 	normale.dir.y = line->pos.y + u * line->dir.y;
// 	normale.dir.z = line->pos.z + u * line->dir.z;
	
// }

unsigned int	shape_finder(t_env *env, t_shapes *shapes, t_line *line)
{
	double			u;
	double			min;
	unsigned int	color;
	// unsigned int	shadow;
	t_sphere		*tmp;

	min = -1;
	color = env->ambiant_light;
	while (shapes)
	{
		if (shapes->type == SPHERE)
		{
			u = sphere_finder((t_sphere *)shapes->content, line);
			if (u >= 0 && (min < 0 || u < min))
			{
				min = u;
				tmp = (t_sphere *)shapes->content;
				color = tmp->color;
			}
		}
		// autres shapes
		shapes = shapes->next;
	}
	// color = get_shadow(env, tmp, line, u);
	return (color);
}

//Fonction Principale
int	minirt(t_vars *vars, t_env *env)
{
	int				i;
	int				j;
	double			ax;
	double			ay;
	t_line			*line;
	unsigned int	color;
	
	j = 0;
	while (j < W_HEIGHT)
	{
		ay = env->camera->fov / W_WIDTH * (W_HEIGHT / 2.0 - (double)j) * M_PI / 180.0;
		i = 0;
		while (i < W_WIDTH)
		{
			ax = env->camera->fov * ((double)i / W_WIDTH - 1.0 / 2.0) * M_PI / 180.0;
			line = linecpy(env->camera, ax, ay);
			if (!line)
				return (1); //free + mlx_loop_end
			color = shape_finder(env, env->shapes, line);
			put_pixel(vars->img, i, j, color);
			i++;
		}
		j++;
	}
	printf("calcul end\n");
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
	return (0); //free + mlx_loop_end
}

int	main(int ac, char **av)
{
	t_vars	*vars;
	t_env	*env;

	if (ac != 2)
		return (ft_putstr_fd("\033[0;31mBad number of arguments\033[0m\n", 2), 2);
	env = parser(av[1]);
	printf("ENV DONE\n");
	vars = init_vars();
	if (!vars)
		return (ft_putstr_fd("\033[0;31mError while generating vars\033[0m\n", 2), 1);
	minirt(vars, env);
	mlx_hook(vars->win, 2, 1L << 0, get_key, vars);
	mlx_hook(vars->win, 17, 1L << 5, mlx_loop_end, vars->mlx);
	mlx_loop(vars->mlx);
	mlx_destroy_image(vars->mlx, vars->img->img);
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	free(vars->img);
	free(vars);
	env_free(env);
	return (0);
}
