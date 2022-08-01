/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 01:56:43 by adesgran          #+#    #+#             */
/*   Updated: 2022/08/01 12:25:03 by adesgran         ###   ########.fr       */
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
void	minirt(t_vars *vars)
{
	(void)vars;
}

int	main(void)
{
	t_vars	*vars;

	vars = init_vars();
	if (!vars)
		return (printf("\033[0;31mError while generating vars\033[0m\n"), 1);
	minirt(vars);
	mlx_hook(vars->win, 2, 1L << 0, get_key, vars);
	mlx_loop(vars->mlx);
	mlx_destroy_image(vars->mlx, vars->img->img);
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	free(vars->img);
	free(vars);
	return (0);
}
