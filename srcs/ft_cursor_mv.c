/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cursor_mv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:27:59 by mrantil           #+#    #+#             */
/*   Updated: 2022/10/28 10:47:49 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

static void	ft_cursor_right(char *input, t_term *term)
{
	if (term->indx < term->bytes)
	{
		if (term->nl_addr[term->c_row + 1])
		{
			if (&input[term->indx] < (term->nl_addr[term->c_row + 1] - 1))
			{
				term->indx++;
				ft_setcursor(++term->c_col, term->c_row);
			}
		}
		else
		{
			term->indx++;
			ft_setcursor(++term->c_col, term->c_row);
		}
	}
}

static void	ft_cursor_left(char *input, t_term *term)
{
	term->indx--;
	term->c_col--;
	if (&input[term->indx + 1] == term->nl_addr[term->c_row])
	{
		if (term->c_row == 1)
			term->c_col = (term->nl_addr[term->c_row] - term->nl_addr[term->c_row - 1]) + (term->prompt_len - 1);
		else
			term->c_col = (term->nl_addr[term->c_row] - term->nl_addr[term->c_row - 1]) + (term->m_prompt_len - 1);
		term->c_row--;
	}
	ft_setcursor(term->c_col, term->c_row);
}

static void	ft_cursor_up(t_term *term, int his)
{
	term->c_col = term->prompt_len;
	ft_setcursor(term->c_col, term->c_row);
	ft_run_capability("ce");
	ft_putstr((char *)vec_get(&term->v_history, term->v_history.len - his));
}

static void	ft_cursor_down(t_term *term, int his)
{
	term->c_col = term->prompt_len;
	ft_setcursor(term->c_col, term->c_row);
	// ft_run_capability("cb");
	// ft_run_capability("cl");
	ft_run_capability("ce");
	ft_putstr((char *)vec_get(&term->v_history, term->v_history.len - his));
}

void	ft_cursor_mv(t_term *term, char *input)
{
	static size_t	his;

	// if (term->nl_addr[term->c_row][-1] == '\n' || term->nl_addr[term->c_row][-1] == '\\')
	// 	term->m_prompt_len = ft_strlen(MINI_PROMPT);
	if (term->ch == 'D' && term->indx)
		ft_cursor_left(input, term);
	else if (term->ch == 'C')
		ft_cursor_right(input, term);
	else if (term->ch == 'A' && his < term->v_history.len)
		ft_cursor_up(term, ++his);
	else if (term->ch == 'B' && his > 0)
		ft_cursor_down(term, --his);
}
