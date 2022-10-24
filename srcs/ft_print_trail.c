/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_trail.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 14:40:06 by mrantil           #+#    #+#             */
/*   Updated: 2022/10/22 16:31:52 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

static void print_line_trail(t_term *term, char *input)
{
	int i;

	i = term->indx;
	while (input[i] && input[i] != '\n')
	{
		write(1, &input[i], 1);
		i++;
	}
}

void	ft_print_trail(t_term *term, char *input)
{
	// ft_run_capability("ce");
	ft_run_capability("vi");
	// ft_run_capability("ic");
	print_line_trail(term, input);
	ft_setcursor(term->c_col, term->c_row);
	ft_run_capability("ve");
}
