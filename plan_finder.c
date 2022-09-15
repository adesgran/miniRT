/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plan_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 16:34:52 by adesgran          #+#    #+#             */
/*   Updated: 2022/09/15 14:04:25 by mchassig         ###   ########.fr       */
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
	norm_vector(&shape->norm.dir);
}

double	plan_finder(t_shapes *shape, t_line *line)
{
	t_plan	*pl;
	t_coord	t;
	double	u;
	double	d;

	norm_vector(&line->dir);
	pl = (t_plan *)shape->content;
	if (fabs((get_angle(&line->dir, &pl->dir) - M_PI / 2)) < 0.001)
		return (-1);
	d = -pl->dir.x * pl->pos.x - pl->dir.y * pl->pos.y - pl->dir.z * pl->pos.z;
	u = -line->pos.x * pl->dir.x - line->pos.y * pl->dir.y
		- line->pos.z * pl->dir.z - d;
	u /= pl->dir.x * line->dir.x + pl->dir.y * line->dir.y
		+ pl->dir.z * line->dir.z;
	if (u < 0)
		return (-1);
	if (pl->r >= 0)
	{
		t.x = line->pos.x + line->dir.x * u;
		t.y = line->pos.y + line->dir.y * u;
		t.z = line->pos.z + line->dir.z * u;
		if (get_dist(&t, &pl->pos) >= pl->r)
			return (-1);
	}
	return (u);
}
