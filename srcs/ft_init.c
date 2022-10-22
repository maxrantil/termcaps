/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:58:29 by mrantil           #+#    #+#             */
/*   Updated: 2022/10/21 14:53:27 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

t_term		*g_term;

void	ft_init(t_term *term)
{
	ft_init_signals();
	term->ch = 0;
	term->bytes = 0;
	term->c_col = 3;
	term->c_row = 0;
	term->total_col = 0;
	term->total_row = 0;
	term->ws_col = 0;
	term->ws_row = 0;
	term->indx = 0;
	term->q_prompt = 0;
	ft_history_get(term);
	g_term = term;
	ft_window_size(term);
}

/* void	kill_process(int sig)
{
	if (sig == 3)
	{
		ft_disable_raw_mode();
		kill(getpid(), SIGINT); //should not kill just give prompt again
	}
} */
