/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_line.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sandruse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 13:43:23 by sandruse          #+#    #+#             */
/*   Updated: 2017/02/28 19:56:16 by sandruse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>
#include <stdio.h>

void	ft_help(t_line *line, t_window *wind)
{
	while (line->x1 != line->x2 || line->y1 != line->y2)
	{
		mlx_pixel_put(wind->mlx, wind->win, line->x1, line->y1, 111111);
		line->error2 = line->error * 2;
		if (line->error2 > -(line->deltay))
		{
			line->error -= line->deltay;
			line->x1 += line->signx;
		}
		if (line->error2 < line->deltax)
		{
			line->error += line->deltax;
			line->y1 += line->signy;
		}
	}
}

void	ft_line(t_pixel_info *a, t_pixel_info *b, t_window *wind)
{
	t_line	*line;

	line = malloc(sizeof(t_line));
	line->x1 = a->default_x;
	line->y1 = a->default_y;
	line->x2 = b->default_x;
	line->y2 = b->default_y;
	if (b->default_z > a->default_z)
	{
		line->color_r = b->current_color_r;
		line->color_g = b->current_color_g;
		line->color_b = b->current_color_b;
	}
	else
	{
		line->color_r = a->current_color_r;
		line->color_g = a->current_color_g;
		line->color_b = a->current_color_b;
	}

	line->deltax = abs(line->x2 - line->x1);
	line->deltay = abs(line->y2 - line->y1);
	if (line->x1 < line->x2)
		line->signx = 1;
	else
		line->signx = -1;
	if (line->y1 < line->y2)
		line->signy = 1;
	else
		line->signy = -1;
	line->error = line->deltax - line->deltay;
	//ft_
	//mlx_pixel_put(wind->mlx, wind->win, line->x2, line->y2, 111111);
	//ft_help(line, wind);
}
