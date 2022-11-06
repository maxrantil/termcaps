/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrow_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:27:59 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/04 14:50:35 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

static void	ft_right(char *input, t_term *term)
{
	if (term->index < term->bytes)
	{
		if (term->nl_addr[term->c_row + 1])
		{
			if (&input[term->index] < (term->nl_addr[term->c_row + 1] - 1))
			{
				term->index++;
				ft_setcursor(++term->c_col, term->c_row);
			}
		}
		else
		{
			term->index++;
			ft_setcursor(++term->c_col, term->c_row);
		}
	}
}

static void	ft_left(char *input, t_term *term)
{
	term->index--;
	term->c_col--;
	if (&input[term->index + 1] == term->nl_addr[term->c_row])
	{
		if (term->c_row == 1)
			term->c_col = term->m_prompt_len;
		else
			term->c_col = term->prompt_len;
		term->c_col += (term->nl_addr[term->c_row]
				- term->nl_addr[--term->c_row]);
	}
	ft_setcursor(term->c_col, term->c_row);
}

void	ft_arrow_input(t_term *term, char *input)
{
	static size_t	his;

	if (term->ch == 'D' && term->index)
		ft_left(input, term);
	else if (term->ch == 'C')
		ft_right(input, term);
	else if (term->ch == 'A' && his < term->v_history.len) //  up
		ft_history_trigger(term, input, ++his);
	else if (term->ch == 'B' && his > 0) // UP assumption
		ft_history_trigger(term, input, --his);
}
