/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history_write_to_file.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 14:59:21 by mrantil           #+#    #+#             */
/*   Updated: 2022/10/25 08:52:08 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/**
 * It writes the history to a file with a maximum och 1024 lines.
 * O_WRONLY access modes: write only 
 * @param term The terminal structure.
 */
void	ft_history_write_to_file(t_term *term)
{
	char	*file;
	size_t	cpy;
	int		fd;

	file = ft_strjoin(getenv("HOME"), "/.42sh_history");
	fd = open(file, O_WRONLY);
	if (fd)
	{
		cpy = 0;
		if (term->v_history.len > 1024)
			cpy = term->v_history.len % 1024;
		while (cpy < term->v_history.len)
		{
			ft_putendl_fd((char *)vec_get(&term->v_history, cpy), fd);
			cpy++;
		}
		close(fd);
	}
	ft_strdel(&file);
}
