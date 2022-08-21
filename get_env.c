/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 19:44:29 by adesgran          #+#    #+#             */
/*   Updated: 2022/08/21 15:25:50 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

t_env	*get_env(void)
{
	t_env		*res;
	t_sphere	*sp;

	res = malloc(sizeof(t_env));
	res->camera = malloc(sizeof(t_camera));
	res->camera->pos.x = 0;
	res->camera->pos.y = 0;
	res->camera->pos.z = 0;
	res->camera->dir.x = 0;
	res->camera->dir.y = 0;
	res->camera->dir.z = 1;
	res->camera->fov = 70.0;
	sp = malloc(sizeof(*sp));
	sp->pos.x = 0;
	sp->pos.y = 0;
	sp->pos.z = 10;
	sp->color = 0xff0000;
	sp->r = 3;
	res->shapes = malloc(sizeof(t_shapes));
	res->shapes->next = NULL;
	res->shapes->content = (void *)sp;
	res->shapes->type = SPHERE;
	return (res);
}
