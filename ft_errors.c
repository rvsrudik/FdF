/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrudenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 14:52:11 by vrudenko          #+#    #+#             */
/*   Updated: 2017/03/02 14:52:16 by vrudenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_error_number_of_params(void)
{
	ft_putstr("usage: ./fdf [file_name]\n");
	exit(0);
}

void	ft_error_wrong_fd(void)
{
	ft_putstr("Can't read from file.\n");
	exit(0);
}

void	ft_error_wrong_map(void)
{
	ft_putstr("Wrong map.");
	exit(0);
}
