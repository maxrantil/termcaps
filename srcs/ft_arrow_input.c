/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrow_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:27:59 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/08 16:37:11 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/**
 * If the cursor is not at the end of the line, move it one space to the right
 *
 * @param input the string that is being edited
 * @param t the struct that holds all the information about the terminal
 */
static void	ft_right(t_term *t, char *input)
{
	if (t->index < t->bytes)
	{
		if (t->nl_addr[t->c_row + 1])
		{
			if (&input[t->index] < (t->nl_addr[t->c_row + 1] - 1))
			{
				t->index++;
				ft_setcursor(++t->c_col, t->c_row);
			}
		}
		else
		{
			t->index++;
			ft_setcursor(++t->c_col, t->c_row);
		}
	}
}

/**
 * It moves the cursor left one character
 *
 * @param input the string that the user is typing in
 * @param t the t_term struct
 */
static void	ft_left(t_term *t, char *input)
{
	if (&input[t->index] == t->nl_addr[t->c_row])
	{
		if (t->c_row == 1)
			t->c_col = t->prompt_len;
		else
			t->c_col = t->m_prompt_len;
		if (t->c_row > 0)
			t->c_col += (t->nl_addr[t->c_row] - t->nl_addr[--t->c_row]);
	}
	t->index--;
	ft_setcursor(--t->c_col, t->c_row);
}

/**
 * It handles the arrow keys
 *
 * @param term the term struct
 * @param input the string that is being edited
 */
void	ft_arrow_input(t_term *term, char *input)
{
	static size_t	his;

	if (term->ch == 'D' && term->index)
		ft_left(term, input);
	else if (term->ch == 'C')
		ft_right(term, input);
	else if (term->ch == 'A' && his < term->v_history.len)
		ft_history_trigger(term, input, ++his);
	else if (term->ch == 'B' && his > 0)
		ft_history_trigger(term, input, --his);
}
