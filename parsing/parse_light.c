/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 13:49:12 by adesgran          #+#    #+#             */
/*   Updated: 2022/09/11 17:45:18 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

void	push_light(t_env *env, t_light *light)
{
	t_light	*tmp;

	light->next = NULL;
	if (env->light == NULL)
		env->light = light;
	else
	{
		tmp = env->light;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = light;
	}
}

int	parse_light(t_env *env, char **tab)
{
	int				err;
	t_light			*light;

	if (env->light)
		return (parsing_error("Light: multiple definitions"), 1);
	if (ft_tablen((void **)tab) != 4)
		return (parsing_error("Light: wrong number of arguments"), 1);
	light = malloc(sizeof(t_light));
	if (!light)
		return (1);
	if (read_coord(tab[1], &(light->pos)))
		return (parsing_error("Light: invalid position coordinates"), 1);
	if (read_color(tab[3], &light->color))
		return (parsing_error("Light: invalid color value"), 1);
	err = 0;
	light->color.i = atod(tab[2], &err);
	if (err || light->color.i > 1.0 || light->color.i < 0.0)
		return (parsing_error("Light: invalid ratio in range"), 1);
	push_light(env, light);
	return (0);
}
