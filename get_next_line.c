/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrudenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 17:49:53 by vrudenko          #+#    #+#             */
/*   Updated: 2017/01/17 17:50:19 by vrudenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int		ft_validation(int fd, int ret, char *buff)
{
	char		buf[1];

	if (fd == -1 || read(fd, buf, 0) == -1)
		return (-1);
	if (!buff && ret == 0)
		return (0);
	return (1);
}

static char		*ft_setfresh(char *fresh, char *buff, char *n, char **line)
{
	char		*temp;

	if (n)
		*n = '\0';
	temp = ft_strjoin(fresh, buff);
	ft_strdel(&fresh);
	fresh = temp;
	if (!n)
		ft_strdel(&buff);
	if (n)
	{
		*line = fresh;
		return (ft_strdup(n + 1));
	}
	return (fresh);
}

static int		ft_facepalm(char **line, char *fresh)
{
	*line = fresh;
	return (1);
}

static char		*ft_setbuff(char *buff, int fd, int *ret)
{
	if (!buff)
	{
		buff = ft_strnew(BUFF_SIZE);
		*ret = read(fd, buff, BUFF_SIZE);
		return (buff);
	}
	return (buff);
}

int				get_next_line(const int fd, char **line)
{
	static char	*buff;
	char		*fresh;
	static int	ret;

	ret = 1;
	if (ft_validation(fd, ret, buff) != 1)
		return (ft_validation(fd, ret, buff));
	fresh = ft_strnew(0);
	while (ret)
	{
		buff = ft_setbuff(buff, fd, &ret);
		if ((ft_strchr(buff, '\n')))
		{
			buff = ft_setfresh(fresh, buff, ft_strchr(buff, '\n'), line);
			return (1);
		}
		else
		{
			fresh = ft_setfresh(fresh, buff, ft_strchr(buff, '\n'), line);
			buff = NULL;
		}
		if (!ret && !buff && *fresh == '\0')
			return (0);
	}
	return (ft_facepalm(line, fresh));
}
