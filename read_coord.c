/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_coord.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 14:00:24 by adesgran          #+#    #+#             */
/*   Updated: 2022/08/21 12:21:15 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

static void	set_error(int *error)
{
	*error = 1;
}

static unsigned int	count_char(char *str, char c)
{
	unsigned int	res;

	res = 0;
	while (*str)
	{
		if (*str == c)
			res++;
		str++;
	}
	return (res);
}

void	read_coord(char *str, t_coord *coord, int *err)
{
	char	**tab;

	coord->x = 0;
	coord->y = 0;
	coord->z = 0;
	*err = 0;
	tab = ft_split(str, ',');
	if (!tab || ft_tablen((void **)tab) != 3 || count_char(str, ',') != 2)
		return (ft_free_tabstr(tab), set_error(err));
	coord->x = atod(tab[0], err);
	if (*err)
		return (ft_free_tabstr(tab));
	coord->y = atod(tab[1], err);
	if (*err)
		return (ft_free_tabstr(tab));
	coord->z = atod(tab[2], err);
	return (ft_free_tabstr(tab));
}
