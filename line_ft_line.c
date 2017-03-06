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

#include "includes/fdf.h"
#include <math.h>
#include <stdio.h>

void	ft_help(t_line *line, t_window *wind, t_data_im_addr *data_im_addr, int color[])
{

	while (line->x1 != line->x2 || line->y1 != line->y2)
	{
		ft_put_pixel_to_image(data_im_addr, line->x1, line->y1, color);
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

void	ft_line(t_pixel_info *a, t_pixel_info *b, t_window *wind, t_image *img, t_data_im_addr *data_im_addr)
{
	t_line	*line;
	int		color[3];

	line = malloc(sizeof(t_line));
	line->x1 = a->current_x;
	line->y1 = a->current_y;
	line->x2 = b->current_x;
	line->y2 = b->current_y;
	if (b->default_z > a->default_z)
	{
		color[0] = b->current_color_r;
		color[1] = b->current_color_g;
		color[2] = b->current_color_b;
	}
	else
	{
		color[0] = a->current_color_r;
		color[1] = a->current_color_g;
		color[2] = a->current_color_b;
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
	ft_help(line, wind, data_im_addr, color);
}
