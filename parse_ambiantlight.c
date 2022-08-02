/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambiantlight.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 15:59:46 by adesgran          #+#    #+#             */
/*   Updated: 2022/08/02 19:08:51 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

int	parse_ambiantlight(t_env *env, char **tab)
{
	int				err;
	double			ratio;
	unsigned int	color;

	if (ft_tablen((void **)tab) != 3)
		return (ft_free_tabstr(tab), 1);
	err = 0;
	ratio = atod(tab[1], &err);
	if (err || ratio < 0.0 || ratio > 1.0)
		return (ft_free_tabstr(tab), 1);
	color = read_color(tab[2], &err);
	if (err)
		return (ft_free_tabstr(tab), 1);
	color = color_ratio(color, ratio);
	env->ambiant_light = color;
	return (ft_free_tabstr(tab), 0);
}
