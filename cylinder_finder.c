/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_finder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 15:13:18 by adesgran          #+#    #+#             */
/*   Updated: 2022/09/01 14:20:04 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

double	cylinder_finder(t_shapes *shape, t_line *line)
{
	t_line		sline;
	t_cylindre	*cylindre;
	double		t;
	double		tp;

	cylindre = (t_cylindre *)shape->content;
	norm_vector(&line->dir);
	norm_vector(&cylindre->dir);
	t = get_t(cylindre, line);
	if (t < 0)
		return (-1);
	coord_cpy(&sline.dir, &cylindre->dir);
	tp = check_collision(cylindre, &sline, line, t);
	if (tp < 0)
		return (tp); //show a plan
	else
		return (tp); //show a sphere
}
