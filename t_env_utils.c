/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_env_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 18:27:11 by adesgran          #+#    #+#             */
/*   Updated: 2022/08/06 15:31:41 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

void	env_free(t_env *env)
{
	if (!env)
		return ;
	printf("%p %p %p\n", env->camera, env->light, env->shapes);
	free(env->camera);
	light_free(env->light);
	shapes_free(env->shapes);
}
