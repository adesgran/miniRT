/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plan.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 15:08:30 by adesgran          #+#    #+#             */
/*   Updated: 2022/09/07 13:33:21 by mchassig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

int	parse_plan(t_env *env, char **tab)
{
	t_plan		*pl;
	t_shapes	*new_shape;

	if (ft_tablen((void **)tab) != 4)
		return (parsing_error("Plane: wrong number of arguments"), 1);
	pl = malloc(sizeof(t_plan));
	if (!pl)
		return (1);
	if (read_coord(tab[1], &(pl->pos)))
		return (parsing_error("Plane: invalid position coordinates"),
			free(pl), 1);
	if (read_coord(tab[2], &(pl->dir)))
		return (parsing_error("Plane: invalid orientation coordinates"),
			free(pl), 1);
	if (check_dir(&pl->dir))
		return (parsing_error("Plane: orientation vector is not normalized"),
			free(pl), 1);
	if (read_color(tab[3], &pl->color))
		return (parsing_error("Plane: invalid color value"), free(pl), 1);
	new_shape = shapes_new(pl, &pl->color, plan_finder);
	if (!new_shape)
		return (free(pl), 1);
	shapes_add(env, new_shape);
	return (0);
}
