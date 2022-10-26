/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_esc_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:31:54 by mrantil           #+#    #+#             */
/*   Updated: 2022/10/20 16:52:30 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

static void	ft_cursor_beginning(t_term *term)
{
	if (!term->c_row)
	{
		term->c_col = term->prompt_len;
		term->indx = 0;
	}
	else
	{
		term->c_col = term->m_prompt_len;
		term->indx = term->nl_addr[term->c_row] - term->nl_addr[0];
	}
	ft_setcursor(term->c_col, term->c_row);
}

char	*get_str_end(char *str)
{
	while (*str)
		str++;
	return (str + 1);
}

static void	ft_cursor_end(char *input, t_term *term)
{
	if (!term->total_row)
	{
		term->c_col = (&input[term->bytes]-  term->nl_addr[term->c_row]) + term->prompt_len;
		term->indx = term->bytes;
	}
	else
	{
		if (term->c_row == term->total_row)
		{
			term->c_col = (get_str_end(term->nl_addr[term->c_row]) -  term->nl_addr[term->c_row]) + 1;
			term->indx = (get_str_end(term->nl_addr[term->c_row]) - term->nl_addr[0]) - 1;
		}
		else
		{
			if (!term->c_row)
				term->c_col = (term->nl_addr[term->c_row + 1] -  term->nl_addr[term->c_row]) + 2;
			else
				term->c_col = (term->nl_addr[term->c_row + 1] -  term->nl_addr[term->c_row]) + 1;
			term->indx = (term->nl_addr[term->c_row + 1] - term->nl_addr[0]) - 1;
		}
	}
	ft_setcursor(term->c_col, term->c_row);
}

static void	shift_arrow(char *input, t_term *term)
{
	if (term->ch == 'D' && term->bytes)
		ft_cursor_beginning(term);
	if (term->ch == 'C' && term->c_col < term->bytes)
		ft_cursor_end(input, term);
}

void	ft_esc_parse(t_term *term, char *input)
{
	term->ch = ft_get_input();
	if (term->ch == '[')
	{
		term->ch = ft_get_input();
		if (term->ch >= 'A' && term->ch <= 'D')
			ft_cursor_mv(term, input);
		if (term->ch == 49)
			ft_alt_cursor_mv(term, input);
		if (term->ch == 'H' && term->bytes)
			ft_cursor_beginning(term);
		if (term->ch == 'F' && term->c_col < term->bytes)
			ft_cursor_end(input, term);
		if (term->ch == '2')
		{
			term->ch = ft_get_input();
			shift_arrow(input, term);
		}
	}
	if (term->ch == 98 || term->ch == 102)
		ft_alt_cursor_mv(term, input);
	term->ch = 0;
}
