/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plan_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 16:34:52 by adesgran          #+#    #+#             */
/*   Updated: 2022/09/11 16:49:59 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

void	plan_norm(t_shapes *shape, t_line *line, double u)
{
	t_plan	*plan;

	plan = (t_plan *)shape->content;
	shape->norm.pos.x = line->pos.x + u * line->dir.x;
	shape->norm.pos.y = line->pos.y + u * line->dir.y;
	shape->norm.pos.z = line->pos.z + u * line->dir.z;
	shape->norm.dir.x = plan->dir.x;
	shape->norm.dir.y = plan->dir.y;
	shape->norm.dir.z = plan->dir.z;
}

double	plan_finder(t_shapes *shape, t_line *line)
{
	t_plan	*plan;
	t_coord	t;
	double	u;
	double	d;
	
	norm_vector(&line->dir);
	plan = (t_plan *)shape->content;
	if (fabs((get_angle(&line->dir, &plan->dir) - M_PI / 2)) < 0.001)
		return (-1);
	d = - (plan->dir.x * plan->pos.x + plan->dir.y * plan->pos.y + plan->dir.z * plan->pos.z);
	u = - (line->pos.x * plan->dir.x + line->pos.y * plan->dir.y + line->pos.z * plan->dir.z + d);
	u /= (plan->dir.x * line->dir.x + plan->dir.y * line->dir.y + plan->dir.z * line->dir.z);
	if (u < 0)
		return (-1);
	if (plan->r >= 0)
	{
		t.x = line->pos.x + line->dir.x * u;
		t.y = line->pos.y + line->dir.y * u;
		t.z = line->pos.z + line->dir.z * u;
		if (get_dist(&t, &plan->pos) >= plan->r)
			return (-1);
	}
	return (u);
}

