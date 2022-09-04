/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plan.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 15:08:30 by adesgran          #+#    #+#             */
/*   Updated: 2022/09/04 15:17:09 by mchassig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

static int	check_value(t_plan *pl)
{
	if (pl->dir.x > 1 || pl->dir.x < 0)
		return (1);
	if (pl->dir.y > 1 || pl->dir.y < 0)
		return (1);
	if (pl->dir.z > 1 || pl->dir.z < 0)
		return (1);
	return (0);
}

int	parse_plan(t_env *env, char **tab)
{
	int			err;
	t_plan		*pl;
	t_shapes	*new_shape;
	
	if (ft_tablen((void **)tab) != 4)
		return (ft_free_tabstr(tab), 1);
	pl = malloc(sizeof(t_plan));
	if (!pl)
		return (ft_free_tabstr(tab), 1);
	err = 0;
	read_coord(tab[1], &(pl->pos), &err);
	if (err)
		return (ft_free_tabstr(tab), 1);
	read_coord(tab[2], &(pl->dir), &err);
	if (err)
		return (ft_free_tabstr(tab), 1);
	read_color(tab[3], &err, &pl->color);
	if (err || check_value(pl))
		return (ft_free_tabstr(tab), 1);
	new_shape = shapes_new(pl, &pl->color, plan_finder);
	if (!new_shape)
		return (ft_free_tabstr(tab), 1);
	shapes_add(env, new_shape);
	return (ft_free_tabstr(tab), 0);
}
