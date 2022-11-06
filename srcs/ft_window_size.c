/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_window_size.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 17:25:07 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/06 18:11:30 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

void	ft_window_size(t_term *term)
{
	struct winsize	size;

	if (ioctl(0, TIOCGWINSZ, (char *)&size) < 0)
		perror("TIOCGWINSZ");
	term->ws_col = size.ws_col;
	term->ws_row = size.ws_row;
	if (*term->inp)
	{
		term->quote = 0;
		term->q_qty = 0;
		setup_nl_addr(term, term->inp);
		ft_setcursor(term->c_col, term->c_row);
		ft_print_trail(term, term->inp);	
	}
}
