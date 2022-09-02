/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambiantlight.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 15:59:46 by adesgran          #+#    #+#             */
/*   Updated: 2022/09/02 14:54:41 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

int	parse_ambiantlight(t_env *env, char **tab)
{
	static int		already_set;
	int				err;

	if (!already_set)
		already_set = 1;
	else
		return (ft_free_tabstr(tab), 1);
	if (!env || !tab || ft_tablen((void **)tab) != 3)
		return (ft_free_tabstr(tab), 1);
	err = 0;
	env->ambiant_light.i = atod(tab[1], &err);
	if (err || env->ambiant_light.i < 0.0 || env->ambiant_light.i > 1.0)
		return (ft_free_tabstr(tab), 1);
	read_color(tab[2], &err, &env->ambiant_light);
	if (err)
		return (ft_free_tabstr(tab), 1);
	return (ft_free_tabstr(tab), 0);
}
