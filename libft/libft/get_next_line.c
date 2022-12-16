/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 15:00:51 by mrantil           #+#    #+#             */
/*   Updated: 2022/10/04 17:16:58 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

static int	cpy_to_static(char **stat_str, char *buffer, int fd)
{
	if (stat_str[fd] != NULL)
		stat_str[fd] = ft_strupdate(stat_str[fd], buffer);
	else
		stat_str[fd] = ft_strdup(buffer);
	return (2);
}

static int	get_line(char **stat_str, char **line, int fd, int i)
{
	char	*temp;

	if (ft_strchr(stat_str[fd], '\n'))
	{
		*line = ft_strsub(stat_str[fd], 0, ft_strclen(stat_str[fd], '\n'));
		temp = ft_strdup(ft_strchr(stat_str[fd], '\n') + 1);
		ft_strdel(&stat_str[fd]);
		stat_str[fd] = temp;
		i = 1;
	}
	else if (i == 0)
	{
		*line = ft_strdup(stat_str[fd]);
		ft_strdel(&stat_str[fd]);
		if (*line[0] != '\0')
			i = 1;
	}
	return (i);
}

int	get_next_line(const int fd, char **line)
{
	static char	*stat_str[FD_MAX];
	char		*buf;
	int			i;

	i = 2;
	buf = (char *)malloc(sizeof(char) * (BUFF_SIZE + 1));
	if (fd < 0 || line == NULL || BUFF_SIZE <= 0 || fd >= FD_MAX)
		i = -1;
	while (i >= 0)
	{
		if (stat_str[fd] != NULL)
			i = get_line(stat_str, line, fd, i);
		if (i == 1 || i == 0)
			break ;
		i = read(fd, buf, BUFF_SIZE);
		if (i > 0)
		{
			buf[i] = '\0';
			i = cpy_to_static(stat_str, buf, fd);
		}
	}
	ft_strdel(&buf);
	return (i);
}
