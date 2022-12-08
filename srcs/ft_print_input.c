/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 22:49:46 by mbarutel          #+#    #+#             */
/*   Updated: 2022/12/08 23:00:31 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

static int	ft_line_len(t_term *t, ssize_t row)
{
	int len;

	if (t->nl_addr[row + 1])
		len = (int)(t->nl_addr[row + 1] - t->nl_addr[row]);
	else
		len = (int)(&t->inp[t->bytes] - t->nl_addr[row]);
	return (len);
}

void	ft_print_input(t_term *t, ssize_t row, int mode)
{
	int		len;
	ssize_t	col;
	
	while (t->nl_addr[row])
	{
		len = ft_line_len(t, row);
		if (ft_is_prompt_line(t, row))
		{
			if (!row)
				col = write(STDOUT_FILENO, PROMPT, t->prompt_len);
			else
				col = write(STDOUT_FILENO, MINI_PROMPT, t->m_prompt_len);
		}
		else
			col = 0;
		col += write(STDOUT_FILENO, t->nl_addr[row], len);
		if (!t->nl_addr[row + 1])
			break ;
		row++;	
	}
	if (mode == 1)
	{
		t->c_row = row;
		t->c_col = col;	
	}
}
