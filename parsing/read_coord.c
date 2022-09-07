/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_coord.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 14:00:24 by adesgran          #+#    #+#             */
/*   Updated: 2022/09/07 13:50:25 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

int	check_dir(t_coord *dir)
{
	if (dir->x > 1 || dir->x < -1)
		return (1);
	if (dir->y > 1 || dir->y < -1)
		return (1);
	if (dir->z > 1 || dir->z < -1)
		return (1);
	norm_vector(dir);
	return (0);
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

int	read_coord(char *str, t_coord *coord)
{
	char	**tab;
	int		err;

	coord->x = 0;
	coord->y = 0;
	coord->z = 0;
	err = 0;
	tab = ft_split(str, ',');
	if (!tab || ft_tablen((void **)tab) != 3 || count_char(str, ',') != 2)
		return (ft_free_tabstr(tab), 1);
	coord->x = atod(tab[0], &err);
	if (err)
		return (ft_free_tabstr(tab), 1);
	coord->y = atod(tab[1], &err);
	if (err)
		return (ft_free_tabstr(tab), 1);
	coord->z = atod(tab[2], &err);
	return (ft_free_tabstr(tab), 0);
}
