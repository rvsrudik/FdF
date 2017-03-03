/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_determ_pixel_info.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrudenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 15:00:48 by vrudenko          #+#    #+#             */
/*   Updated: 2017/03/02 15:00:49 by vrudenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	ft_set_default_colors(t_pixel_info *pixel_info)
{
	pixel_info->default_color_r = 255;
	pixel_info->default_color_g = 255;
	pixel_info->default_color_b = 255;
}

static void	ft_set_current_color(t_pixel_info *pixel_info)
{
	pixel_info->current_color_r = pixel_info->default_color_r;
	pixel_info->current_color_g = pixel_info->default_color_g;
	pixel_info->current_color_b = pixel_info->default_color_b;
}

static void ft_determ_pixel_color(t_pixel_info *pixel_info, char *color)
{
	char color_hex[3];
	color_hex[2] = '\0';

	pixel_info->default_color_r = 0;
	pixel_info->default_color_g = 0;
	pixel_info->default_color_b = 0;
	if (color)
	{
		while (*color != '\0')
			color++;
		color--;
		color_hex[1] = *(color);
		color--;
		color_hex[0] = *(color);
		if (!ft_strchr(color_hex, 'x'))
		{
			pixel_info->default_color_b = ft_hex_to_dig(color);
			color--;
			color_hex[1] = *(color);
			color--;
			color_hex[0] = *(color);
			if (!ft_strchr(color_hex, 'x'))
			{
				pixel_info->default_color_g = ft_hex_to_dig(color);
				color--;
				color_hex[1] = *(color);
				color--;
				color_hex[0] = *(color);
				if (!ft_strchr(color_hex, 'x'))
					pixel_info->default_color_r = ft_hex_to_dig(color);
			}
		}
	}
}

void		ft_determ_pixel_info(int y, t_pixel_info **pixels_arr,
		t_window *window, char **pixels_from_line)
{
	int				start_pixel;
	int				i;
	char			**hight_agn_color;
	t_pixel_info	*pixel_info;

	i = 0;
	start_pixel = y * window->pixels_width;
	while (i < window->pixels_width)
	{
		hight_agn_color = ft_strsplit(pixels_from_line[i], ',');
		pixels_arr[start_pixel] = (t_pixel_info*)malloc(sizeof(t_pixel_info));
		pixels_arr[start_pixel]->current_y = y;
		pixels_arr[start_pixel]->default_y = y;
		pixels_arr[start_pixel]->current_x = i;
		pixels_arr[start_pixel]->default_x = i;
		pixels_arr[start_pixel]->default_z = ft_atoi(hight_agn_color[0]);
		pixels_arr[start_pixel]->current_z = ft_atoi(hight_agn_color[0]);
		ft_determ_pixel_color(pixels_arr[start_pixel], hight_agn_color[1]);
		start_pixel++;
		i++;
	}
	ft_memdel((void**)pixels_from_line);
}
