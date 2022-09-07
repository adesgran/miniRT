/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 14:44:07 by adesgran          #+#    #+#             */
/*   Updated: 2022/09/06 18:28:12 by mchassig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

void	parsing_error(char *msg)
{
	ft_putstr_fd("\033[0;31m[ParsingError] > ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\033[0m\n", 2);
}
