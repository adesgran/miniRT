/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 01:58:25 by adesgran          #+#    #+#             */
/*   Updated: 2022/09/10 15:55:37 by mchassig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

static t_data	*img_init(void *mlx)
{
	t_data	*img;

	img = malloc(sizeof(t_data));
	if (!img)
		return (NULL);
	img->img = mlx_new_image(mlx, W_WIDTH, W_HEIGHT);
	if (!img->img)
		return (free(img), NULL);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, \
		&img->line_length, &img->endian);
	if (!img->addr)
	{
		mlx_destroy_image(mlx, img->img);
		return (free(img), NULL);
	}
	return (img);
}

t_vars	*init_vars(void)
{
	t_vars	*vars;

	vars = malloc(sizeof(t_vars));
	if (!vars)
		return (NULL);
	vars->mlx = mlx_init();
	if (!vars->mlx)
		return (free(vars), NULL);
	vars->win = mlx_new_window(vars->mlx, W_WIDTH, W_HEIGHT, "miniRT");
	if (!vars->win)
	{
		mlx_destroy_display(vars->mlx);
		return (free(vars->mlx), free(vars), NULL);
	}
	vars->img = img_init(vars->mlx);
	if (vars->img == NULL)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		mlx_destroy_display(vars->mlx);
		return (free(vars->mlx), free(vars), NULL);
	}
	return (vars);
}
