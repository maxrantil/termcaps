/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history_get.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 14:56:28 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/29 16:41:46 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/*
 * It reads the history file and stores it in a vector
 *
 * @param t the terminal structure
 */
void	ft_history_get(t_term *t)
{
	char	*buf;
	int		fd;

	vec_new(&t->v_history, 0, sizeof(char) * BUFF_SIZE);
	t->history_file = ft_history_file_get();
	fd = open(t->history_file, O_RDONLY | O_CREAT, 0644);
	if (fd)
	{
		buf = NULL;
		while (get_next_line(fd, &buf) > 0)
		{
			vec_push(&t->v_history, buf);
			ft_strdel(&buf);
		}
		ft_strdel(&buf);
		close(fd);
	}
}
