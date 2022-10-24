/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history_get.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 14:56:28 by mrantil           #+#    #+#             */
/*   Updated: 2022/10/24 13:39:18 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/*
**	O_CREAT If pathname does not exist, create it as a regular file.
**	O_RDONLY access modes: read/write
**	S_IRWXU  00700 user (file owner) has read, write, and execute permission	
*/

void	ft_history_get(t_term *term)
{
	char	*buf;
	char	*file;
	int		fd;

	vec_new(&term->v_history, 0, sizeof(char) * 256);
	file = ft_strjoin(getenv("HOME"), "/.42sh_history");
	fd = open(file, O_CREAT, O_RDONLY);
	while (get_next_line(fd, &buf) > 0)
	{
		vec_push(&term->v_history, buf);
		ft_strdel(&buf);
	}
	close(fd);
	ft_strdel(&file);
}
