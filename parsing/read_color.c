/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 16:56:35 by adesgran          #+#    #+#             */
/*   Updated: 2022/09/02 15:34:33 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

static unsigned int	next_size(char *str)
{
	if (ft_isdigit(*str))
		return (next_size(str + 1) + 1);
	return (0);
}

static int	check_form(char *str)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (!*str)
			return (1);
		if (next_size(str) > 3 || next_size(str) == 0)
			return (1);
		while (ft_isdigit(*str))
			str++;
		if ((*str != ',' && i != 2) || (*str && i == 2))
			return (1);
		if (*str == ',')
			str++;
		i++;
	}
	return (0);
}

static void	set_err(int *err)
{
	*err = 1;
}

static void	fill_color(t_color *color, unsigned int res)
{
	static int	state;

	if (!state)
		state = 0;
	printf("State = %u\n", state);
	if (state == 0)
		color->r = res;
	else if (state == 1)
		color->g = res;
	else if (state == 2)
		color->b = res;
	state++;
	if (state > 2)
		state = 0;
}

void	read_color(char *str, int *err, t_color *color)
{
	unsigned int	tmp;
	unsigned int	i;

	i = 0;
	if (check_form(str))
		return (set_err(err));
	while (i < 3)
	{
		tmp = ft_atoi(str);
		if (tmp > 255)
			return (set_err(err));
		fill_color(color, tmp);
		while (ft_isdigit(*str))
			str++;
		if (*str == ',')
			str++;
		i++;
	}
}
