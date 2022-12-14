/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchassig <mchassig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 00:56:24 by adesgran          #+#    #+#             */
/*   Updated: 2022/08/01 18:27:30 by mchassig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

void	put_pixel(t_data *img, int x, int y, ...)
{
	va_list	args;
	char	*dst;

	va_start(args, y);
	if (x < 0 || y < 0 || x >= W_WIDTH || y >= W_HEIGHT)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = va_arg(args, unsigned int);
	va_end(args);
}
