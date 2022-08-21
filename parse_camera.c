/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 12:21:46 by adesgran          #+#    #+#             */
/*   Updated: 2022/08/21 12:48:39 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

static int	check_dir(t_coord dir)
{
	if (dir.x > 1 || dir.x < -1)
		return (1);
	if (dir.y > 1 || dir.y < -1)
		return (1);
	if (dir.z > 1 || dir.z < -1)
		return (1);
	return (0);
}

int parse_camera(t_env *env, char **tab)
{
	int	err;

	err = 0;
	if (!tab || !env || ft_tablen((void **)tab) != 4)
		return (ft_free_tabstr(tab), 1);
	env->camera = malloc(sizeof(t_camera));
	if (!env->camera)
		return (ft_free_tabstr(tab), 1);
	read_coord(tab[1], &env->camera->pos, &err);
	if (err)
		return (ft_free_tabstr(tab), 1);
	read_coord(tab[2], &env->camera->dir, &err);
	if (err)
		return (ft_free_tabstr(tab), 1);
	if (check_dir(env->camera->dir))
		return (ft_free_tabstr(tab), 1);
	env->camera->fov = atod(tab[3], &err);
	if (err || env->camera->fov > 180 || env->camera->fov < 0)
		return (ft_free_tabstr(tab), 1);
	return (ft_free_tabstr(tab), 0);
}
