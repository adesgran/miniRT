/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_env_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 18:27:11 by adesgran          #+#    #+#             */
/*   Updated: 2022/08/21 13:48:19 by adesgran         ###   ########.fr       */
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
	free(env);
}
