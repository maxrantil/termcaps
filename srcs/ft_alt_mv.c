/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alt_mv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 09:05:53 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/25 16:48:16 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

static void	ft_alt_mv_left(t_term *term, char *input)
{
	while (term->indx && ft_isspace(&input[term->indx - 1]))
		term->indx--;
	while (term->indx && !ft_isspace(&input[term->indx - 1]))
		term->indx--;
	term->c_col = &input[term->indx] - term->nl_addr[term->c_row];
	if (!term->c_row)
		term->c_col += term->prompt_len;
	else
		term->c_col += term->m_prompt_len;
	ft_setcursor(term->c_col, term->c_row);
}

static void	ft_alt_mv_right(t_term *term, char *input)
{
	while (term->indx < term->bytes && ft_isspace(&input[term->indx]))
		term->indx++;
	while (term->indx < term->bytes && !ft_isspace(&input[term->indx]))
		term->indx++;
	term->c_col = &input[term->indx] - term->nl_addr[term->c_row];
	if (!term->c_row)
		term->c_col += term->prompt_len;
	else
		term->c_col += term->m_prompt_len;
	ft_setcursor(term->c_col, term->c_row);
}

static void	ft_alt_mv_up(char *input, t_term *term)
{
	size_t	len;
	size_t	index;

	index = &input[term->indx] - term->nl_addr[term->c_row];
	len = term->nl_addr[term->c_row] - term->nl_addr[term->c_row - 1];
	if (index < len)
	{
		if (term->c_row == 1)
		{
			if (index < term->prompt_len)
				term->c_col = term->prompt_len;
			else
				index--;
		}
		term->indx = (&term->nl_addr[term->c_row - 1][index]
				- term->nl_addr[0]);
	}
	else
	{
		if (term->c_row == 1)
			term->c_col = len + (term->prompt_len - 1);
		else
			term->c_col = len + (term->prompt_len - term->m_prompt_len);
		term->indx = (term->nl_addr[term->c_row] - term->nl_addr[0]) - 1;
	}
	term->c_row--;
	ft_setcursor(term->c_col, term->c_row);
}

static void	ft_alt_mv_down(char *input, t_term *term)
{
	size_t	len;
	size_t	index;

	index = &input[term->indx] - term->nl_addr[term->c_row];
	if (term->c_row < (term->total_row - 1))
		len = term->nl_addr[term->c_row + 2] - term->nl_addr[term->c_row + 1];
	else
		len = &input[term->bytes] - term->nl_addr[term->c_row + 1];
	if (index < len)
	{
		if (!term->c_row)
			term->indx = &term->nl_addr[term->c_row + 1][index]
				- term->nl_addr[0] + 1;
		else
			term->indx = &term->nl_addr[term->c_row + 1][index]
				- term->nl_addr[0];
	}
	else
	{
		term->c_col = len + (term->m_prompt_len - 1);
		if (term->c_row < (term->total_row - 1))
			term->indx = &term->nl_addr[term->c_row + 2][-1] - term->nl_addr[0];
		else
			term->indx = (get_str_end(term->nl_addr[term->c_row + 1])
					- term->nl_addr[0]) - 1;
	}
	term->c_row++;
	ft_setcursor(term->c_col, term->c_row);
}

void	ft_alt_cursor_mv(t_term *term, char *input)
{
	if (term->ch == 98 && &input[term->indx] > term->nl_addr[term->c_row])
		ft_alt_mv_left(term, input);
	else if (term->ch == 102 && term->indx < term->bytes)
	{
		if (term->nl_addr[term->c_row + 1])
		{
			if (&input[term->indx] < &term->nl_addr[term->c_row + 1][-1])
				ft_alt_mv_right(term, input);
		}
		else
			ft_alt_mv_right(term, input);
	}
	else if (term->ch == 49)
	{
		term->ch = ft_get_input();
		if (term->ch == 59)
		{
			term->ch = ft_get_input();
			if (term->ch == 51)
			{
				term->ch = ft_get_input();
				if (term->ch == 65 && term->c_row)
					ft_alt_mv_up(input, term);
				if (term->ch == 66 && term->c_row < term->total_row)
					ft_alt_mv_down(input, term);
				term->ch = 0;
			}
		}
	}
}
