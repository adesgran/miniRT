/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_shapes_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 13:34:02 by adesgran          #+#    #+#             */
/*   Updated: 2022/08/01 13:34:41 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

t_shapes	*shapes_init(void *content, int type)
{
	t_shapes	*res;

	res = malloc(sizeof(t_shapes));
	if (!res)
		return (NULL);
	res->content = content;
	res->type = type;
	res->next = NULL;
	return (res);
}

void	shapes_add(t_shapes *shapes, void *content, int type)
{
	while (shapes->next)
		shapes = shapes->next;
	shapes->next = malloc(sizeof(t_shapes));
	if (!shapes->next)
		return ;
	shapes = shapes->next;
	shapes->content = content;
	shapes->type = type;
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
