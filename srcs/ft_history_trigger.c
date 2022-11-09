/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history_trigger.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 10:59:10 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/09 10:08:19 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/**
 * It moves the cursor to the end of the term->inp
 *
 * @param term the term structure
 * @param term->inp the term->inp string
 */
static void	ft_history_trigger_end(t_term *term)
{
	term->index = term->bytes;
	term->c_row = term->total_row;
	if (ft_is_prompt_line(term, term->c_row))
	{
		if (!term->c_row)
			term->c_col = term->prompt_len;
		else
			term->c_col = term->m_prompt_len;
	}
	term->c_col += &term->inp[term->bytes] - term->nl_addr[term->c_row];
	ft_setcursor(term->c_col, term->total_row);
	ft_run_capability("ve");
}

/**
 * It resets the terminal to its initial state
 *
 * @param term the term structure
 */
static void	ft_history_trigger_start(t_term *term)
{
	ft_run_capability("vi");
	term->quote = 0;
	term->q_qty = 0;
	term->c_col = 0;
	term->c_row = 0;
	term->total_row = 0;
	ft_setcursor(term->c_col, term->c_row);
	ft_run_capability("cd");
	ft_putstr(PROMPT);
}

/**
 * It takes the term->inp,
 * copies it to a temporary variable, then copies the history entry to the term->inp
 * and prints it
 *
 * @param term the term struct
 * @param term->inp the term->inp buffer
 * @param his the history number to go to.
 */
void	ft_history_trigger(t_term *term, int his)
{
	char	*history;

	ft_history_trigger_start(term);
	history = (char *)vec_get(&term->v_history, term->v_history.len - his);
	if (history)
	{
		term->bytes = ft_strlen(history);
		if (!term->input_cpy)
			term->input_cpy = ft_strdup(term->inp);
		ft_memset((void *)term->inp, '\0', BUFF_SIZE);
		ft_memcpy((void *)term->inp, (void *)history, term->bytes);
	}
	else
	{
		term->bytes = ft_strlen(term->input_cpy);
		ft_memset((void *)term->inp, '\0', BUFF_SIZE);
		ft_memcpy((void *)term->inp, (void *)term->input_cpy, term->bytes);
		ft_strdel(&term->input_cpy);
	}
	ft_reset_nl_addr(term);
	ft_print_trail(term);
	ft_history_trigger_end(term);
}
