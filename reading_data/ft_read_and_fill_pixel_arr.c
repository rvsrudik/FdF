/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_and_fill_pixel_arr.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrudenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 15:25:46 by vrudenko          #+#    #+#             */
/*   Updated: 2017/03/02 15:25:47 by vrudenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	**ft_pixels_line_to_array(char *line, t_window *window)
{
	char	**pixels_from_line;
	pixels_from_line = ft_strsplit(line, ' ');

	return (pixels_from_line);
}

void	ft_read_and_fill_pixel_arr(t_allstruct *allstruct,
		char **pixels_line_array, int fd)
{
	int		y;
	char	*line;
	int		pixels_in_line;

	pixels_in_line = 0;
	y = 0;
	ft_determ_pixel_info(y, allstruct->pixels_arr,
	allstruct->window, pixels_line_array);
	y++;
	while (y < allstruct->window->pixels_hight)
	{
		get_next_line(fd, &line);
		if (line[0] == '\0')
			ft_error_wrong_map();
		pixels_line_array = ft_pixels_line_to_array(line, allstruct->window);
		while (pixels_line_array[pixels_in_line])
			pixels_in_line++;
		if (pixels_in_line != allstruct->window->pixels_width)
			ft_error_wrong_map();
		ft_determ_pixel_info(y, allstruct->pixels_arr,
		allstruct->window, pixels_line_array);
		y++;
	}
}
