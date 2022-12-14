/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 01:56:43 by adesgran          #+#    #+#             */
/*   Updated: 2022/09/15 13:42:57 by mchassig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

void	free_mlx(t_vars *vars)
{
	mlx_destroy_image(vars->mlx, vars->img->img);
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	free(vars->img);
	free(vars);
}

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

void	show_all(t_vars *vars, unsigned int tab[W_HEIGHT][W_WIDTH])
{
	int	i;
	int	j;

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
}

int	main(int ac, char **av)
{
	t_vars			*vars;
	t_env			*env;
	unsigned int	tab_color[W_HEIGHT][W_WIDTH];

	if (ac != 2)
		return (ft_putstr_fd("\033[0;31mWrong number of arguments\033[0m\n", 2)
			, 2);
	env = parser(av[1]);
	if (!env)
		return (1);
	minirt(env, tab_color);
	vars = init_vars();
	if (!vars)
		return (ft_putstr_fd("\033[0;31mUnable to generate mlx vars\033[0m\n", 2),
			env_free(env), 1);
	show_all(vars, tab_color);
	mlx_hook(vars->win, 2, 1L << 0, get_key, vars);
	mlx_hook(vars->win, 17, 1L << 5, mlx_loop_end, vars->mlx);
	mlx_loop(vars->mlx);
	return (free_mlx(vars), env_free(env), 0);
}
