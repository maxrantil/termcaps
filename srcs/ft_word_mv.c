/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_word_mv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:43:30 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/09 10:03:17 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

static void	ft_word_left(t_term *term)
{
	while (term->index && ft_isspace(&term->inp[term->index - 1]))
	{
		if (&term->inp[term->index + 1] == term->nl_addr[term->c_row])
			break ;
		term->index--;
	}
	while (term->index && !ft_isspace(&term->inp[term->index - 1]))
	{
		if (&term->inp[term->index] == term->nl_addr[term->c_row])
			break ;
		term->index--;
	}
	term->c_col = &term->inp[term->index] - term->nl_addr[term->c_row];
	if (term->nl_addr[term->c_row] == &term->inp[0])
		term->c_col += term->prompt_len;
	else if (ft_is_prompt_line(term, term->c_row))
		term->c_col += term->m_prompt_len;
	ft_setcursor(term->c_col, term->c_row);
}

static void	ft_word_right(t_term *term)
{
	size_t	row;

	row = term->c_row + 1;
	while (term->index < term->bytes && ft_isspace(&term->inp[term->index]))
	{
		if (term->nl_addr[row] \
		&& &term->inp[term->index + 1] == term->nl_addr[row])
			break ;
		term->index++;
	}
	while (term->index < term->bytes && !ft_isspace(&term->inp[term->index]))
	{
		if (term->nl_addr[row] \
		&& &term->inp[term->index + 1] == term->nl_addr[row])
			break ;
		term->index++;
	}
	term->c_col = &term->inp[term->index] - term->nl_addr[row - 1];
	if (term->nl_addr[row - 1] == &term->inp[0])
		term->c_col += term->prompt_len;
	else if (ft_is_prompt_line(term, row - 1))
		term->c_col += term->m_prompt_len;
	ft_setcursor(term->c_col, row - 1);
}

void	ft_word_mv(t_term *term)
{
	if (term->ch == 98 && (&term->inp[term->index] > term->nl_addr[term->c_row]))
		ft_word_left(term);
	else if (term->ch == 102 && (term->index < term->bytes))
	{
		if (term->nl_addr[term->c_row + 1])
		{
			if (&term->inp[term->index] < &term->nl_addr[term->c_row + 1][-1])
				ft_word_right(term);
		}
		else
			ft_word_right(term);
	}
}
