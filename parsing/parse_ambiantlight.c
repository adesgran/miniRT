/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambiantlight.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 15:59:46 by adesgran          #+#    #+#             */
/*   Updated: 2022/09/06 18:25:11 by mchassig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

int	parse_ambiantlight(t_env *env, char **tab)
{
	int				err;

	if (env->ambiant_light)
		return (parsing_error("Ambiant Light: multiple definitions"), 1);
	if (ft_tablen((void **)tab) != 3)
		return (parsing_error("Ambiant Light: wrong number of arguments"), 1);
	env->ambiant_light = malloc(sizeof(t_color));
	if (!env->ambiant_light)
		return (1);
	err = 0;
	env->ambiant_light->i = atod(tab[1], &err);
	if (err || env->ambiant_light->i < 0.0 || env->ambiant_light->i > 1.0)
		return (parsing_error("Ambiant Light: invalid ratio in range"), 1);
	if (read_color(tab[2], env->ambiant_light))
		return (parsing_error("Ambiant Light: invalid color value"), 1);
	return (0);
}
