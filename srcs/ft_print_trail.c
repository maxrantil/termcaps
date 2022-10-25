/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_trail.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 14:40:06 by mrantil           #+#    #+#             */
/*   Updated: 2022/10/25 16:31:48 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

static void print_line_trail(t_term *term, char *input)
{
	int i;

	i = term->indx;
	if (term->nl_addr[term->c_row + 1])
	{
		write(1, &input[i], (term->nl_addr[term->c_row + 1] - &input[i]) - 1);
	}
	else
		write(1, &input[i], ft_strlen(&input[i]));
}

void	ft_print_trail(t_term *term, char *input)
{
	ft_run_capability("vi");
	print_line_trail(term, input);
	ft_setcursor(term->c_col, term->c_row);
	ft_run_capability("ve");
}
