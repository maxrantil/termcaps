/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_trail.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 14:40:06 by mrantil           #+#    #+#             */
/*   Updated: 2022/10/20 16:03:43 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

void	ft_print_trail(t_term *term, char *input)
{
	// tputs(tgetstr("vi", NULL), 1, ft_putc);
	run_capability("vi");
	ft_putstr(&input[term->c_col]);
	ft_setcursor(term->c_col, term->c_row);
	run_capability("ve");
	// tputs(tgetstr("ve", NULL), 1, ft_putc);
}
