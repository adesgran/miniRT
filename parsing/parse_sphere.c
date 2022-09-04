/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 13:17:39 by adesgran          #+#    #+#             */
/*   Updated: 2022/09/04 15:18:34 by mchassig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

int	parse_sphere(t_env *env, char **tab)
{
	int			err;
	t_sphere	*sp;
	t_shapes	*new_shape;
	
	if (ft_tablen((void **)tab) != 4)
		return (ft_free_tabstr(tab), 1);
	sp = malloc(sizeof(t_sphere));
	if (!sp)
		return (ft_free_tabstr(tab), 1);
	err = 0;
	read_coord(tab[1], &(sp->pos), &err);
	if (err)
		return (ft_free_tabstr(tab), 1);
	sp->r = atod(tab[2], &err) / 2;
	if (err || sp->r < 0)
		return (ft_free_tabstr(tab), 1);
	read_color(tab[3], &err, &sp->color);
	if (err)
		return (ft_free_tabstr(tab), 1);
	new_shape = shapes_new(sp, &sp->color, sphere_finder);
	if (!new_shape)
		return (ft_free_tabstr(tab), 1);
	shapes_add(env, new_shape);
	return (ft_free_tabstr(tab), 0);
}
