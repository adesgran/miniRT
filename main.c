/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 01:56:43 by adesgran          #+#    #+#             */
/*   Updated: 2022/08/28 17:00:25 by adesgran         ###   ########.fr       */
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
	norm_vector(&line->dir);
	matrix_rotation(&(line->dir), ax, ay);
	return (line);
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
	unsigned int	tab[W_HEIGHT][W_WIDTH];
	
	j = 0;
	while (j < W_HEIGHT)
	{
		ax = env->camera->fov / W_WIDTH * (W_HEIGHT / 2.0 - (double)j) * M_PI / 180.0;
		i = 0;
		while (i < W_WIDTH)
		{
			ay = env->camera->fov * ((double)i / W_WIDTH - 1.0 / 2.0) * M_PI / 180.0;
			line = linecpy(env->camera, -ax, ay);
			if (!line)
				return (1); //free + mlx_loop_end
			color = shapes_finder(env, env->shapes, line);
			tab[i][j] = color;
			free(line);
			i++;
		}
		j++;
	}
	printf("calcul end\n");
	j = 0;
	while (j < W_HEIGHT)
	{
		i = 0;
		while (i < W_WIDTH)
		{
			put_pixel(vars->img, i, j, tab[i][j]);
			i++;
		}
		j++;
	}
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
	norm_vector(&env->camera->dir);
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
