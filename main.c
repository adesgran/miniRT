/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 01:56:43 by adesgran          #+#    #+#             */
/*   Updated: 2022/08/21 13:54:15 by adesgran         ###   ########.fr       */
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

//Fonction Principale
void	minirt(t_vars *vars, t_env *env)
{
	if (!env)
	{
		printf("ERROR EMPTY ENV\n");
		return ;
	}
	printf("Color : %x\n", env->ambiant_light);
	if (env->light)
		printf("LIGHT: Color=%x pos=%f/%f/%f\n", env->light->color, env->light->pos.x, env->light->pos.y, env->light->pos.z);
	if (env->camera)
		printf("CAMERA : Fov=%f pos=%f/%f/%f dir=%f/%f/%f\n", env->camera->fov, env->camera->pos.x, env->camera->pos.y, env->camera->pos.z, env->camera->dir.x, env->camera->dir.y, env->camera->dir.z);
	t_shapes *shapes = env->shapes;
	while (shapes)
	{
		if (shapes->type == SPHERE)
		{
			t_sphere *sp = shapes->content;
			printf("SPHERE : pos=%f/%f/%f r=%f color=%x\n", sp->pos.x, sp->pos.y, sp->pos.z, sp->r, sp->color);
		}
		shapes = shapes->next;
	}

	(void)vars;
	(void)env;
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
