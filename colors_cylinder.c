/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_cylinder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 11:55:59 by adesgran          #+#    #+#             */
/*   Updated: 2022/09/01 14:18:44 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

unsigned int	get_cy_(t_env *env, t_cylindre *cy, t_line *line, double u)
{
	t_line		sline;
	double		t;
	double		tp;

	norm_vector(&line->dir);
	norm_vector(&cy->dir);
	t = get_t(cy, line);
	if (t < 0)
		return (-1);
	coord_cpy(&sline.dir, &cy->dir);
	tp = check_collision(cy, &sline, line, t);
	if (tp < 0)
		return (tp); //show a plan
	else
		return (tp); //show a sphere
}

