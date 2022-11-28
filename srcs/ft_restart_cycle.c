/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_restart_cycle.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:56:42 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/28 12:24:44 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

void	ft_restart_cycle(t_term *t)
{
	ft_putendl_fd(t->inp, STDOUT_FILENO);
	ft_memset(t->inp, '\0', BUFFSIZE);
	t->quote = 0;
	t->q_qty = 0;
	t->bytes = 0;
	t->index = 0;
	t->heredoc = 0;
	t->c_col = t->prompt_len;
	t->start_row = ft_get_linenbr();
	t->total_row = 0;
	t->c_row = t->total_row;
	ft_add_nl_last_row(t, 0);
	ft_strdel(&t->delim);
	write(1, PROMPT, (size_t)t->prompt_len);
	ft_setcursor(t->c_col, t->c_row + t->start_row);
}
