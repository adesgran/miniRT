/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 14:57:25 by adesgran          #+#    #+#             */
/*   Updated: 2022/08/03 13:46:46 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

static int	is_space(char c)
{
	if (c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == '\v')
		return (1);
	return (0);
}

static unsigned int	strs_len(char *str)
{
	unsigned int	res;

	res = 0;
	while (*str)
	{
		if (!is_space(*str))
		{
			res++;
			while (!is_space(*str) && *str)
				str++;
		}
		while (is_space(*str) && *str)
			str++;
	}
	return (res);
}

static unsigned int	str_len(char *str)
{
	unsigned int	res;

	res = 0;
	while (str[res] && !is_space(str[res]))
		res++;
	return (res);
}

char	**split_spaces(char *str)
{
	char			**res;
	unsigned int	size;
	unsigned int	i;

	size = strs_len(str);
	if (!size)
		return (NULL);
	res = malloc(sizeof(char *) * (size + 1));
	if (!res)
		return (res);
	i = 0;
	while (i < size)
	{
		res[i] = ft_strndup(str, (size_t)str_len(str));
		if (!res[i])
			return (ft_free_tabstr(res), NULL);
		i++;
		str += str_len(str);
		while (is_space(*str))
			str++;
	}
	res[i] = NULL;
	return (res);
}
