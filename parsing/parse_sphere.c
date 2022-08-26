/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 13:17:39 by adesgran          #+#    #+#             */
/*   Updated: 2022/08/26 15:07:02 by mchassig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

int	parse_sphere(t_env *env, char **tab)
{
	int			err;
	t_sphere	*sp;

	if (ft_tablen((void **)tab) != 4)
		return (ft_free_tabstr(tab), 1);
	sp = malloc(sizeof(t_sphere));
	if (!sp)
		return (ft_free_tabstr(tab), 1);
	if (env->shapes)
		shapes_add(env->shapes, sp, SPHERE, sphere_finder);
	else
		env->shapes = shapes_init(sp, SPHERE, sphere_finder);
	err = 0;
	read_coord(tab[1], &(sp->pos), &err);
	if (err)
		return (ft_free_tabstr(tab), 1);
	sp->r = atod(tab[2], &err) / 2;
	if (err || sp->r < 0)
		return (ft_free_tabstr(tab), 1);
	sp->color = read_color(tab[3], &err);
	if (err)
		return (ft_free_tabstr(tab), 1);
	return (ft_free_tabstr(tab), 0);
}
