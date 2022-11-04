/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 18:17:16 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/04 14:18:08 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

extern t_term	*g_term;

static void	sig_handler(int num)
{
	if (num == SIGWINCH)
	{
		ft_window_size(g_term);
		setup_nl_addr(g_term, char *input)
	}
	/* if (num == SIGINT)
	{
		ft_disable_raw_mode();
		exit(130);
	} */
}

void	ft_init_signals(void)
{
	/* signal(SIGINT, sig_handler); */
	signal(SIGWINCH, sig_handler);
}
