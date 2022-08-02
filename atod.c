/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atod.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 16:03:35 by adesgran          #+#    #+#             */
/*   Updated: 2022/08/02 16:47:26 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

static double	int_atod(char *str, double *d)
{
	*d = 0;
	if (ft_strlen(str) >= 37)
		return (1);
	while (ft_isdigit(*str))
	{
		*d *= 10;
		*d += (double)(*str - '0');
		str++;
	}
	return (0);
}

static double	rev_atod(char *str)
{
	double	res;
	int		i;

	res = 0;
	i = 0;
	while (ft_isdigit(str[i]))
	{
		res += (double)(str[i] - '0') / pow(10, i + 1);
		i++;
	}
	return (res);
}

double	atod(char *str, int *error)
{
	double	res;
	double	tmp;

	*error = int_atod(str, &res);
	if (*error)
		return (0);
	while (ft_isdigit(*str))
		str++;
	if (!*str)
		return (res);
	if (*str != '.')
	{
		*error = 1;
		return (0);
	}
	str++;
	tmp = (double)rev_atod(str);
	res += tmp;
	while (ft_isdigit(*str))
		str++;
	if (*str == '\0')
		return (res);
	*error = 1;
	return (0);
}
