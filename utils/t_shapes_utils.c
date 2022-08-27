/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_shapes_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 13:34:02 by adesgran          #+#    #+#             */
/*   Updated: 2022/08/27 18:58:46 by mchassig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

t_shapes	*shapes_init(void *content, int type, double (*ft_finder)(void *, t_line *))
{
	t_shapes	*res;

	res = malloc(sizeof(t_shapes));
	if (!res)
		return (NULL);
	res->content = content;
	res->type = type;
	res->ft_finder = ft_finder;
	res->next = NULL;
	return (res);
}

void	shapes_add(t_shapes *shapes, void *content, int type, double (*ft_finder)(void *, t_line *))
{
	while (shapes->next)
		shapes = shapes->next;
	shapes->next = malloc(sizeof(t_shapes));
	if (!shapes->next)
		return ;
	shapes = shapes->next;
	shapes->content = content;
	shapes->type = type;
	shapes->ft_finder = ft_finder;
	shapes->next = NULL;
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
