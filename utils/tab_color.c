/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 15:37:02 by adesgran          #+#    #+#             */
/*   Updated: 2022/09/15 15:38:46 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

void	free_tab_color(unsigned int **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

unsigned int	**set_table(void)
{
	unsigned int	**res;
	int				i;

	res = malloc(sizeof(*res) * (W_HEIGHT + 1));
	if (!res)
		return (res);
	i = 0;
	while (i < W_HEIGHT)
	{
		res[i] = malloc(sizeof(**res) * (W_WIDTH));
		if (!res[i])
		{
			while (i >= 0)
			{
				free(res[i]);
				i--;
			}
			return (free(res), NULL);
		}
		i++;
	}
	res[i] = NULL;
	return (res);
}
