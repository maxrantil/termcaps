/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_esc_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:31:54 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/09 10:07:49 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

static void	ft_cursor_beginning(t_term *term)
{
	if (!term->c_row)
	{
		term->c_col = term->prompt_len;
		term->index = 0;
	}
	else
	{
		if (ft_is_prompt_line(term, term->c_row))
			term->c_col = term->m_prompt_len;
		else
			term->c_col = 0;
		term->index = term->nl_addr[term->c_row] - term->nl_addr[0];
	}
	ft_setcursor(term->c_col, term->c_row);
}

static void	ft_cursor_end(t_term *term)
{
	size_t	len;

	len = term->index;
	term->c_col = 0;
	if (!term->c_row || ft_is_prompt_line(term, term->c_row))
	{
		if (!term->c_row)
			term->c_col = term->prompt_len;
		else
			term->c_col = term->m_prompt_len;
	}
	if (term->nl_addr[term->c_row + 1])
		term->index = (term->nl_addr[term->c_row + 1] - term->nl_addr[0]) - 1;
	else
		term->index = term->bytes;
	len = term->index - len;
	term->c_col += &term->inp[term->index] - term->nl_addr[term->c_row];
	ft_setcursor(term->c_col, term->c_row);
}

static void	shift_arrow(t_term *term)
{
	if (term->ch == 'D' && term->bytes)
		ft_cursor_beginning(term);
	if (term->ch == 'C')
		ft_cursor_end(term);;
}

/**
 * It parses the escape sequences and calls the appropriate function
 * 
 * @param term the t_term struct
 * @param term->inp the string that the user is typing
 */
void	ft_esc_parse(t_term *term)
{
	term->ch = ft_get_input();
	if (term->ch == '[')
	{
		term->ch = ft_get_input();
		if (term->ch >= 'A' && term->ch <= 'D')
			ft_arrow_input(term);
		if (term->ch == 49)
			ft_opt_mv(term);
		if (term->ch == 'H' && term->bytes)
			ft_cursor_beginning(term);
		if (term->ch == 'F')
			ft_cursor_end(term);
		if (term->ch == '2')
		{
			term->ch = ft_get_input();
			shift_arrow(term);
		}
	}
	if (term->ch == 98 || term->ch == 102)
		ft_opt_mv(term);
	term->ch = 0;
}
