/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 13:49:12 by adesgran          #+#    #+#             */
/*   Updated: 2022/08/06 15:48:51 by adesgran         ###   ########.fr       */
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
	/*  TO SET FOR MANDATORY PART
   else
   		return (free(light));
	*/
}


int parse_light(t_env *env, char **tab)
{
	int				err;
	t_light			*light;
	unsigned int	color;
	double			ratio;

	if (ft_tablen((void **)tab) != 4)
		return (ft_free_tabstr(tab), 1);
	light = malloc(sizeof(t_light));
	if (!light)
		return (ft_free_tabstr(tab), 1);
	err = 0;
	printf("tab[1] = %s\n", tab[1]);
	read_coord(tab[1], &(light->pos),  &err);
	if (err)
		return (free(light), ft_free_tabstr(tab), 1);
	color = read_color(tab[3], &err);
	if (err)
		return (free(light), ft_free_tabstr(tab), 1);
	ratio = atod(tab[2], &err);
	if (err || ratio > 1.0 || ratio < 0.0)
		return (free(light), ft_free_tabstr(tab), 1);
	light->color = color_ratio(color, ratio);
	push_light(env, light);
	return (ft_free_tabstr(tab), 0);
}
