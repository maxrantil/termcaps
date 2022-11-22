/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:58:29 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/22 12:56:19 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

t_term	*g_t;

void	ft_init(t_term *t)
{
	ft_init_signals();
	t->ch = 0;
	ft_memset(t->inp, '\0', BUFFSIZE);
	t->start_row = ft_get_linenbr();
	t->quote = 0;
	t->q_qty = 0;
	t->bslash = 0;
	t->bytes = 0;
	t->c_row = 0;
	t->total_row = 0;
	t->ws_col = 0;
	t->ws_row = 0;
	t->index = 0;
	ft_history_get(t);
	g_t = t;
	t->nl_addr = NULL;
	t->delim = NULL;
	ft_window_size(t);
	t->prompt_len = (ssize_t)ft_strlen(PROMPT);
	t->m_prompt_len = (ssize_t)ft_strlen(MINI_PROMPT);
	t->c_col = t->prompt_len;
	t->input_cpy = NULL;
	t->heredoc = 0;
	t->total_row_cpy = 0;
}
