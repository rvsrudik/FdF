/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew_bchar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrudenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 14:36:35 by vrudenko          #+#    #+#             */
/*   Updated: 2017/01/19 14:40:22 by vrudenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	*ft_strnew_bchar(size_t size, char c)
{
	char		*str;
	size_t		i;

	i = 0;
	if ((str = (char*)(malloc(size + 1))) == NULL)
		return (NULL);
	str[size] = '\0';
	while (i < size)
	{
		str[i] = c;
		i++;
	}
	return (str);
}
