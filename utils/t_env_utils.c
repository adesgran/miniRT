/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_env_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 18:27:11 by adesgran          #+#    #+#             */
/*   Updated: 2022/09/06 18:15:19 by mchassig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

void	env_free(t_env *env)
{
	if (!env)
		return ;
	free(env->camera);
	light_free(env->light);
	shapes_free(env->shapes);
	free(env->ambiant_light);
	free(env);
}
