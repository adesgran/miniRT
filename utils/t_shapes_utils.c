/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_shapes_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 13:34:02 by adesgran          #+#    #+#             */
/*   Updated: 2022/09/11 16:33:55 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

t_shapes	*shapes_new(void *content, t_color *color,
	double (*ft_finder)(t_shapes *, t_line *),
	void (*ft_norm)(struct s_shapes *, t_line *, double))
{
	t_shapes	*res;

	res = malloc(sizeof(t_shapes));
	if (!res)
		return (NULL);
	res->content = content;
	res->ft_finder = ft_finder;
	res->ft_norm = ft_norm;
	color_cpy(color, &res->color);
	res->next = NULL;
	return (res);
}

void	shapes_add(t_env *env, t_shapes *new)
{
	t_shapes	*tmp;

	if (!env->shapes)
	{
		env->shapes = new;
		return ;
	}
	tmp = env->shapes;
	while (tmp && tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	shapes_free(t_shapes *shapes)
{
	t_shapes	*tmp;

	while (shapes)
	{
		tmp = shapes;
		shapes = shapes->next;
		free(tmp->content);
		free(tmp);
	}
}
