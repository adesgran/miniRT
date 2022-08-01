/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 01:58:25 by adesgran          #+#    #+#             */
/*   Updated: 2022/08/01 12:25:27 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

static t_data	*window_init(void *mlx, void **mlx_win)
{
	t_data	*img;

	*mlx_win = mlx_new_window(mlx, W_WIDTH, W_HEIGHT, "miniRT");
	img = malloc(sizeof(t_data));
	if (!img)
		return (NULL);
	img->img = mlx_new_image(mlx, W_WIDTH, W_HEIGHT);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, \
		&img->line_length, &img->endian);
	return (img);
}

t_vars	*init_vars(void)
{
	t_vars	*vars;

	vars = malloc(sizeof(t_vars));
	if (!vars)
		return (NULL);
	vars->mlx = mlx_init();
	vars->win = NULL;
	vars->img = window_init(vars->mlx, &vars->win);
	if (vars->img == NULL)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		free(vars);
		return (NULL);
	}
	return (vars);
}
