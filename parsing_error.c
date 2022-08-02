/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adesgran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 14:44:07 by adesgran          #+#    #+#             */
/*   Updated: 2022/08/02 14:46:50 by adesgran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

void	parsing_error(char *msg)
{
	ft_putstr_fd("\033[0;31m[ParsingError] > ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\033[0m\n", 2);
}