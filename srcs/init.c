/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:58:29 by mrantil           #+#    #+#             */
/*   Updated: 2022/10/20 13:37:55 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

void	init(t_term *term)
{
	term->ch = 0;
	term->col = 0;
	term->cursor = 0;
	term->row = 0;
	term->cur_row = 0;
}

/* void	kill_process(int sig)
{
	if (sig == 3)
	{
		disable_raw_mode();
		kill(getpid(), SIGINT); //should not kill just give prompt again
	}
} */
