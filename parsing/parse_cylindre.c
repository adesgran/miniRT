/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylindre.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 14:09:07 by adesgran          #+#    #+#             */
/*   Updated: 2022/09/11 17:45:56 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

static int	check_value(t_cylindre *cy)
{
	if (cy->r < 0 || cy->h < 0)
		return (1);
	if (cy->dir.x > 1 || cy->dir.x < 0)
		return (1);
	if (cy->dir.y > 1 || cy->dir.y < 0)
		return (1);
	if (cy->dir.z > 1 || cy->dir.z < 0)
		return (1);
	if (cy->dir.x == 0 && cy->dir.y == 0 && cy->dir.z == 0)
		return (1);
	return (0);
}

static int	read_args(t_cylindre *cy, char **tab)
{
	int	err;

	err = 0;
	if (read_coord(tab[1], &(cy->pos)))
		return (parsing_error("Cylinder: invalid position coordinates"), 1);
	if (read_coord(tab[2], &(cy->dir)))
		return (parsing_error("Cylinder: invalid orientation coordinates"), 1);
	cy->r = atod(tab[3], &err) / 2;
	if (err)
		return (parsing_error("Cylinder: invalid diameter"), 1);
	cy->h = atod(tab[4], &err);
	if (err)
		return (parsing_error("Cylinder: invalid height"), 1);
	if (read_color(tab[5], &cy->color) || check_value(cy))
		return (parsing_error("Cylinder: invalid color value"), 1);
	norm_vector(&cy->dir);
	return (0);
}

static int	add_plan(t_env *env, t_cylindre *cy, int coeff)
{
	t_plan		*p;
	t_shapes	*new_shape;

	p = malloc(sizeof(*p));
	if (!p)
		return (1);
	coord_cpy(&p->dir, &cy->dir);
	p->r = cy->r;
	p->pos.x = cy->pos.x + coeff * cy->dir.x * cy->h / 2;
	p->pos.y = cy->pos.y + coeff * cy->dir.y * cy->h / 2;
	p->pos.z = cy->pos.z + coeff * cy->dir.z * cy->h / 2;
	color_cpy(&cy->color, &p->color);
	new_shape = shapes_new(p, &p->color, plan_finder, plan_norm);
	if (!new_shape)
		return (free(p), 1);
	shapes_add(env, new_shape);
	return (0);
}

int	parse_cylindre(t_env *env, char **tab)
{
	t_cylindre	*cy;
	t_shapes	*new_shape;

	if (ft_tablen((void **)tab) != 6)
		return (parsing_error("Cylinder: wrong number of arguments"), 1);
	cy = malloc(sizeof(t_cylindre));
	if (!cy)
		return (1);
	if (read_args(cy, tab))
		return (free(cy), 1);
	new_shape = shapes_new(cy, &cy->color, cylinder_finder, cylinder_norm);
	if (!new_shape)
		return (free(cy), 1);
	shapes_add(env, new_shape);
	if (add_plan(env, cy, 1) || add_plan(env, cy, -1))
		return (1);
	return (0);
}
