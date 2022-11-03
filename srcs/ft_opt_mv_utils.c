/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_opt_mv_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 14:24:52 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/03 15:15:26 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

void	word_left(t_term *term, char *input)
{
	while (term->index && ft_isspace(&input[term->index - 1]))
	{
		if (&input[term->index + 1] == term->nl_addr[term->c_row])
			break ;
		term->index--;
	}
	while (term->index && !ft_isspace(&input[term->index - 1]))
	{
		if (&input[term->index] == term->nl_addr[term->c_row])
			break ;
		term->index--;
	}
	term->c_col = &input[term->index] - term->nl_addr[term->c_row];
	if (term->nl_addr[term->c_row] == &input[0])
		term->c_col += term->prompt_len;
	else if (is_prompt_line(term, term->c_row))
		term->c_col += term->m_prompt_len;
	ft_setcursor(term->c_col, term->c_row);
}

void	word_right(t_term *term, char *input)
{
	size_t	row;

	row = term->c_row + 1;
	while (term->index < term->bytes && ft_isspace(&input[term->index]))
	{
		if (term->nl_addr[row] && &input[term->index + 1] == term->nl_addr[row])
			break ;
		term->index++;
	}
	while (term->index < term->bytes && !ft_isspace(&input[term->index]))
	{
		if (term->nl_addr[row] && &input[term->index + 1] == term->nl_addr[row])
			break ;
		term->index++;
	}
	term->c_col = &input[term->index] - term->nl_addr[row - 1];
	if (term->nl_addr[row - 1] == &input[0])
		term->c_col += term->prompt_len;
	else if (is_prompt_line(term, row - 1))
		term->c_col += term->m_prompt_len;
	ft_setcursor(term->c_col, row - 1);
}

static size_t	get_prompt_len(t_term *term, int num)
{
	size_t	prompt_len;

	prompt_len = 0;
	if (term->c_row == 1 && (num < 0))
		prompt_len = term->prompt_len;
	else if (is_prompt_line(term, term->c_row + num))
		prompt_len = term->m_prompt_len;
	return (prompt_len);
}

void	line_up(t_term *term)
{
	size_t	len;
	size_t	prompt_len;

	len = term->nl_addr[term->c_row] - term->nl_addr[term->c_row - 1];
	prompt_len = get_prompt_len(term, -1);
	if (term->c_col < (len + prompt_len))
	{
		if (term->c_col < prompt_len)
		{
			term->c_col = prompt_len;
			if (term->c_row == 1)
				term->index = 0;
			else
				term->index = term->nl_addr[term->c_row - 1] - term->nl_addr[0];
		}
		else
			term->index = (&term->nl_addr[term->c_row - 1]
				[term->c_col - prompt_len] - term->nl_addr[0]);
	}
	else
	{
		term->c_col = (len + prompt_len) - 1;
		term->index = (term->nl_addr[term->c_row] - term->nl_addr[0]) - 1;
	}
	ft_setcursor(term->c_col, --term->c_row);
}

void	line_down(char *input, t_term *term)
{
	size_t	len;
	size_t	prompt_len;

	prompt_len = get_prompt_len(term, 1);
	if (term->c_row < (term->total_row - 1))
		len = (term->nl_addr[term->c_row + 2] - term->nl_addr[term->c_row + 1]);
	else
		len = &input[term->bytes] - term->nl_addr[term->c_row + 1];
	if (term->c_col < (len + prompt_len))
		term->index = &term->nl_addr[term->c_row + 1]
		[term->c_col - prompt_len] - term->nl_addr[0];
	else
	{
		term->c_col = len + prompt_len;
		if (term->c_row < (term->total_row - 1))
		{
			term->c_col--;
			term->index = &term->nl_addr[term->c_row + 2][-1]
				- term->nl_addr[0];
		}
		else
			term->index = (&input[term->bytes] - term->nl_addr[0]);
	}
	ft_setcursor(term->c_col, ++term->c_row);
}
