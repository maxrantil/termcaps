/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:58:29 by mrantil           #+#    #+#             */
/*   Updated: 2022/10/20 17:11:06 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

void	ft_init(t_term *term)
{
	term->ch = 0;
	term->bytes = 0;
	term->c_col = 0;
	term->c_row = 0;
	term->total_col = 0;
	term->total_row = 0;
}

/* void	kill_process(int sig)
{
	if (sig == 3)
	{
		disable_raw_mode();
		kill(getpid(), SIGINT); //should not kill just give prompt again
	}
} */
