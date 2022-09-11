/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 13:17:39 by adesgran          #+#    #+#             */
/*   Updated: 2022/09/11 16:32:21 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

int	parse_sphere(t_env *env, char **tab)
{
	int			err;
	t_sphere	*sp;
	t_shapes	*new_shape;

	if (ft_tablen((void **)tab) != 4)
		return (parsing_error("Sphere: wrong number of arguments"), 1);
	sp = malloc(sizeof(t_sphere));
	if (!sp)
		return (1);
	if (read_coord(tab[1], &(sp->pos)))
		return (parsing_error("Sphere: invalid position coordinates"),
			free(sp), 1);
	err = 0;
	sp->r = atod(tab[2], &err) / 2;
	if (err || sp->r < 0)
		return (parsing_error("Sphere: invalid diameter"), free(sp), 1);
	if (read_color(tab[3], &sp->color))
		return (parsing_error("Sphere: invalid color value"), free(sp), 1);
	new_shape = shapes_new(sp, &sp->color, sphere_finder, sphere_norm);
	if (!new_shape)
		return (free(sp), 1);
	shapes_add(env, new_shape);
	return (0);
}
