/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history_get.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 14:56:28 by mrantil           #+#    #+#             */
/*   Updated: 2022/10/21 15:16:36 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/*
**	O_CREAT If pathname does not exist, create it as a regular file.
**	O_RDONLY access modes: read/write
**	S_IRWXU  00700 user (file owner) has read, write, and execute permission	
*/

void	ft_get_history(t_term *term)
{
	char	*buf;
	int		fd;

	vec_new(&term->v_history, 0, sizeof(char) * 256);
	fd = open(".42sh_history", O_CREAT | O_RDONLY | S_IRWXU);
	if (fd)
	{
		while (get_next_line(fd, &buf) > 0)
		{
			vec_push(&term->v_history, buf);
			ft_strdel(&buf);
		}
		close(fd);
	}
	return ;
}
