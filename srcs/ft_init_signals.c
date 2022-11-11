/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 18:17:16 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/09 10:18:14 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

extern t_term	*g_t;
/**
 * It sets the signal handler for the SIGWINCH signal to the sig_handler function
 *
 * @param num The signal number.
 */
static void	sig_handler(int num)
{
	if (num == SIGWINCH)
		ft_window_size(g_t);
}

/**
 * It initializes the signal handler for the SIGWINCH signal
 */
void	ft_init_signals(void)
{
	signal(SIGWINCH, sig_handler);
}
