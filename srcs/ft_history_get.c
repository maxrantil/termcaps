/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history_get.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 14:56:28 by mrantil           #+#    #+#             */
/*   Updated: 2022/10/25 08:49:436 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/**
 * It reads the history file and stores it in a vector
 * O_CREAT If pathname does not exist, create it as a regular file.
 * O_RDONLY access modes: read/write
 * @param term The terminal structure.
 */
void	ft_history_get(t_term *term)
{
	char	*buf;
	char	*file;
	int		fd;

	vec_new(&term->v_history, 0, sizeof(char) * 256);
	file = ft_strjoin(getenv("HOME"), "/.42sh_history");
	fd = open(file, O_RDONLY | O_CREAT, 0644);
	if (fd)
	{
		while (get_next_line(fd, &buf) > 0)
		{
			vec_push(&term->v_history, buf);
			ft_strdel(&buf);
		}
		ft_strdel(&buf);
		close(fd);
	}
	ft_strdel(&file);
}
