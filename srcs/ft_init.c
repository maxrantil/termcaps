/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:58:29 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/28 12:18:58 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

t_term	*g_t;

void	ft_init(t_term *t)
{
	ft_init_signals();
	ft_memset(t->inp, '\0', BUFFSIZE);
	ft_memset(t, 0, sizeof(t));
	t->start_row = ft_get_linenbr();
	ft_history_get(t);
	g_t = t;
	ft_window_size(t);
	t->prompt_len = (ssize_t)ft_strlen(PROMPT);
	t->m_prompt_len = (ssize_t)ft_strlen(MINI_PROMPT);
	t->c_col = t->prompt_len;
}
