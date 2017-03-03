/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex_to_dig.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrudenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 15:55:16 by vrudenko          #+#    #+#             */
/*   Updated: 2017/03/02 15:55:18 by vrudenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	ft_convert_hex_digit_to_dig(int dig)
{
	char	*tmp;

	if (ft_isdigit(dig))
		dig -= '0';
	else if ((tmp = ft_strchr("abcdef", dig)))
	{
		dig = *tmp - 'a' + 10;
	}
	else if ((tmp = ft_strchr("ABCDEF", dig)))
	{
		dig = *tmp - 'A' + 10;
	}
	return (dig);
}

int			ft_hex_to_dig(char color[])
{
	int		digit1_hex;
	int		digit2_hex;
	int		digit1_dec;
	int		digit2_dec;

	if (color[0] == 'x' || color[1] == 'x')
		return (0);
	digit1_hex = color[0];
	digit2_hex = color[1];
	digit1_dec = ft_convert_hex_digit_to_dig(digit1_hex);
	digit2_dec = ft_convert_hex_digit_to_dig(digit2_hex);
	return ((digit1_dec * 16) + digit2_dec);
}
