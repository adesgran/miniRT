/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 13:41:20 by mchassig          #+#    #+#             */
/*   Updated: 2022/09/15 15:55:42 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

static t_line	*linecpy(t_camera *camera, double ax, double ay)
{
	t_line	*line;

	line = malloc(sizeof(t_line));
	if (!line)
		return (NULL);
	line->dir.x = camera->dir.x;
	line->dir.y = camera->dir.y;
	line->dir.z = camera->dir.z;
	norm_vector(&line->dir);
	matrix_rotation(&(line->dir), ax, ay);
	line->pos.x = camera->pos.x + line->dir.x * 0.00001;
	line->pos.y = camera->pos.y + line->dir.y * 0.00001;
	line->pos.z = camera->pos.z + line->dir.z * 0.00001;
	return (line);
}

void	print_per(double x)
{
	ft_printf("\r%d%%", (int)x);
}

int	minirt(t_env *env, unsigned int **tab_color)
{
	int				i;
	int				j;
	double			ax;
	double			ay;
	t_line			*line;

	j = -1;
	while (++j < W_HEIGHT)
	{
		ax = env->camera->fov / W_WIDTH * (W_HEIGHT / 2.0 - (double)j)
			* M_PI / 180.0;
		i = -1;
		while (++i < W_WIDTH)
		{
			ay = env->camera->fov * ((double)i / W_WIDTH - 1.0 / 2.0)
				* M_PI / 180.0;
			line = linecpy(env->camera, -ax, ay);
			if (!line)
				return (1);
			tab_color[i][j] = shapes_finder(env, env->shapes, line);
			free(line);
		}
		ft_printf("\r%d%%", (int)(0.5 + 100 * (double)j / W_HEIGHT));
	}
	return (0);
}
