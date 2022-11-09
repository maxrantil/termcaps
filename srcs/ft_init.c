/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:58:29 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/09 09:52:22 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

t_term	*g_term;

void	ft_init(t_term *term)
{
	ft_init_signals();
	term->ch = 0;
	ft_memset(term->inp, '\0', BUFFSIZE);
	term->quote = 0;
	term->q_qty = 0;
	term->bytes = 0;
	term->c_row = 0;
	term->total_row = 0;
	term->ws_col = 0;
	term->ws_row = 0;
	term->index = 0;
	ft_history_get(term);
	g_term = term;
	term->nl_addr = NULL;
	ft_window_size(term);
	term->prompt_len = ft_strlen(PROMPT);
	term->m_prompt_len = ft_strlen(MINI_PROMPT);
	term->c_col = term->prompt_len;
	term->input_cpy = NULL;
	term->total_row_cpy = 0;
}
