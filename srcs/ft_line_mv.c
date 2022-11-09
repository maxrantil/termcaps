/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_line_mv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:41:49 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/09 10:10:16 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/**
 * It returns the length of the prompt on the line that the cursor is moving to
 * 
 * @param term the term struct
 * @param num the number of lines to move up or down
 * 
 * @return The length of the prompt.
 */
static size_t	ft_mv_prompt_len(t_term *term, int num)
{
	size_t	prompt_len;

	prompt_len = 0;
	if (term->c_row == 1 && (num < 0))
		prompt_len = term->prompt_len;
	else if (ft_is_prompt_line(term, term->c_row + num))
		prompt_len = term->m_prompt_len;
	return (prompt_len);
}

/**
 * It moves the cursor down one line
 * 
 * @param input the input string
 * @param term the t_term struct
 */
static void	ft_line_down(t_term *term)
{
	size_t	len;
	size_t	prompt_len;

	prompt_len = ft_mv_prompt_len(term, 1);
	if (term->c_row < (term->total_row - 1))
		len = (term->nl_addr[term->c_row + 2] - term->nl_addr[term->c_row + 1]);
	else
		len = &term->inp[term->bytes] - term->nl_addr[term->c_row + 1];
	if (term->c_col < (len + prompt_len))
	{
		if (term->c_col < prompt_len)
		{
			term->c_col = prompt_len;
			term->index = term->nl_addr[term->c_row + 1] - term->nl_addr[0];
		}
		term->index = &term->nl_addr[term->c_row + 1][term->c_col - prompt_len] - term->nl_addr[0];
	}
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
			term->index = (&term->inp[term->bytes] - term->nl_addr[0]);
	}
	ft_setcursor(term->c_col, ++term->c_row);
}

/**
 * It moves the cursor up one line, and sets the cursor to the same 
 * column as it was on the previous line
 * 
 * @param term the terminal structure
 */
static void	ft_line_up(t_term *term)
{
	size_t	len;
	size_t	prompt_len;

	len = term->nl_addr[term->c_row] - term->nl_addr[term->c_row - 1];
	prompt_len = ft_mv_prompt_len(term, -1);
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

/**
 * It handles the up and down arrow keys
 * 
 * @param term the structure that holds all the information about the terminal
 * @param input the string that the user is typing
 */
void	ft_line_mv(t_term *term)
{
	term->ch = ft_get_input();
	if (term->ch == 59)
	{
		term->ch = ft_get_input();
		if (term->ch == 51)
		{
			term->ch = ft_get_input();
			if (term->ch == 65 && term->c_row)
				ft_line_up(term);
			if (term->ch == 66 && term->c_row < term->total_row)
				ft_line_down(term);
			term->ch = 0;
		}
	}
}
