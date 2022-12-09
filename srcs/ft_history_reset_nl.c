/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history_reset_nl.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 10:29:50 by mbarutel          #+#    #+#             */
/*   Updated: 2022/12/09 13:05:32 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/**
 * It resets the newline addresses of the history buffer
 * 
 * @param t the term struct
 * @param inp the string to be printed
 */
void	ft_history_reset_nl(t_term *t, char *inp)
{
	ssize_t	i;
	ssize_t	col;
	ssize_t	row;

	i = -1;
	col = 0;
	row = t->c_row;
	while (inp[++i])
	{
		col++;
		if (((col + ft_get_prompt_len(t, row))) == t->ws_col || inp[i] == '\n')
		{
			row++;
			col = 0;
			t->total_row++;
			ft_add_nl_last_row(t, inp, i + 1);
		}
	}
	t->bytes = &inp[i] - t->nl_addr[0];
	t->index = t->bytes;
}
