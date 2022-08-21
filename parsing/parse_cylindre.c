/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylindre.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 14:09:07 by adesgran          #+#    #+#             */
/*   Updated: 2022/08/21 15:26:40 by adesgran         ###   ########.fr       */
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
	return (0);
}

static int	read_args(t_cylindre *cy, char **tab)
{
	int			err;

	err = 0;
	read_coord(tab[1], &(cy->pos), &err);
	if (err)
		return (ft_free_tabstr(tab), 1);
	read_coord(tab[2], &(cy->dir), &err);
	if (err)
		return (ft_free_tabstr(tab), 1);
	cy->r = atod(tab[3], &err) / 2;
	if (err)
		return (ft_free_tabstr(tab), 1);
	cy->h = atod(tab[4], &err);
	if (err)
		return (ft_free_tabstr(tab), 1);
	cy->color = read_color(tab[5], &err);
	if (err || check_value(cy))
		return (ft_free_tabstr(tab), 1);
	return (0);
}

int	parse_cylindre(t_env *env, char **tab)
{
	t_cylindre	*cy;

	if (ft_tablen((void **)tab) != 6)
		return (ft_free_tabstr(tab), 1);
	cy = malloc(sizeof(t_cylindre));
	if (!cy)
		return (ft_free_tabstr(tab), 1);
	if (env->shapes)
		shapes_add(env->shapes, cy, CYLINDRE);
	else
		env->shapes = shapes_init(cy, CYLINDRE);
	if (read_args(cy, tab))
		return (1);
	return (ft_free_tabstr(tab), 0);
}
