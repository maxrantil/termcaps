/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 09:38:04 by mrantil           #+#    #+#             */
/*   Updated: 2022/10/17 15:16:05 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"

void	write_history_to_file(t_msh *msh)
{
	size_t	cpy;
	int		fd;

	fd = open(".msh_history", O_WRONLY);
	if (fd)
	{
		cpy = 0;
		if (msh->v_history.len > 1024)
			cpy = msh->v_history.len % 1024;
		while (cpy < msh->v_history.len)
		{
			ft_putendl_fd((char *)vec_get(&msh->v_history, cpy), fd);
			cpy++;
		}
		close(fd);
	}
	return ;
}

/*
**	O_CREAT If pathname does not exist, create it as a regular file.
**	O_WRONLY access modes: read/write
**	O_RDONLY access modes: read/write
**	O_APPEND The  file  is  opened  in append mode.
**	S_IRWXU  00700 user (file owner) has read, write, 
**	and execute permissionS_IRUSR  00400 user has read permission	
*/

void	get_history(t_msh *msh)
{
	char	*buf;
	int		fd;

	fd = open(".msh_history", O_CREAT | O_RDONLY | S_IRWXU);
	if (fd)
	{
		while (get_next_line(fd, &buf) > 0)
		{
			vec_push(&msh->v_history, buf);
			ft_strdel(&buf);
		}
		close(fd);
	}
	return ;
}

void	history(t_msh *msh, int status)
{
	size_t	num_incr;

	if (status == 1 && msh->cl[0] == 'h' && msh->cl[1] == 'i' && msh->cl[2] == 's' && msh->cl[3] == 't' && msh->cl[4] == 'o' && msh->cl[5] == 'r' && msh->cl[6] == 'y')
	{
		num_incr = 0;
		while (++num_incr <= msh->v_history.len)
		{
			ft_putnbr(num_incr);
			write(1, "  ", 2);
			ft_putendl((char *)vec_get(&msh->v_history, num_incr));

		}
	}
	else if (status == 1 && msh->cl[0] == '^')
		ft_printf("%s\n", vec_get(&msh->v_history, msh->v_history.len - ft_strlen(msh->cl)));
	else if (status == 2)
		vec_push(&msh->v_history, msh->cl);
}
