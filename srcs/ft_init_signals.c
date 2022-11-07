/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 18:17:16 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/07 14:14:41 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

extern t_term	*g_term;
/**
 * It sets the signal handler for the SIGWINCH signal to the sig_handler function
 *
 * @param num The signal number.
 */
static void	sig_handler(int num)
{
	if (num == SIGWINCH)
		ft_window_size(g_term);
/*
	if (num == SIGINT)
	{
		ft_disable_raw_mode();
		exit(130);
	}
*/
}

/* void	kill_process(int sig)
{
	if (sig == 3)
	{
		ft_disable_raw_mode();
		kill(getpid(), SIGINT); //should not kill just give prompt again
	}
} */

/**
 * It initializes the signal handler for the SIGWINCH signal
 */
void	ft_init_signals(void)
{
	/* signal(SIGINT, sig_handler); */
	signal(SIGWINCH, sig_handler);
}
