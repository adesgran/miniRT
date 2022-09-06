/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 12:21:46 by adesgran          #+#    #+#             */
/*   Updated: 2022/09/06 18:30:14 by mchassig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

int	parse_camera(t_env *env, char **tab)
{
	int	err;

	if (env->camera)
		return (parsing_error("Camera: multiple definitions"), 1);
	if (ft_tablen((void **)tab) != 4)
		return (parsing_error("Camera: wrong number of arguments"), 1);
	env->camera = malloc(sizeof(t_camera));
	if (!env->camera)
		return (1);
	if (read_coord(tab[1], &env->camera->pos))
		return (parsing_error("Camera: invalid position coordinates"), 1);
	if (read_coord(tab[2], &env->camera->dir))
		return (parsing_error("Camera: invalid orientation coordinates"), 1);
	if (check_dir(&env->camera->dir))
		return (parsing_error("Camera: orientation vector is not normalized"),
			1);
	err = 0;
	env->camera->fov = atod(tab[3], &err);
	if (err || env->camera->fov > 180 || env->camera->fov < 0)
		return (parsing_error("Camera: invalid FOV"), 1);
	return (0);
}
