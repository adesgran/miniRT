/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrncmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 12:43:00 by mchassig          #+#    #+#             */
/*   Updated: 2022/03/03 13:06:32 by mchassig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strrncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = ft_strlen(s1) - 1;
	j = ft_strlen(s2) - 1;
	k = 0;
	while (k < n)
	{
		if (s1[i - k] != s2[j - k])
			return ((unsigned char)s1[i - k] - (unsigned char)s2[j - k]);
		k++;
	}
	return (0);
}
