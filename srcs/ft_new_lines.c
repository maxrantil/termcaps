/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_lines.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 13:42:45 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/27 20:20:15 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

void	nl_backslash(t_term *term, char *input)
{
	term->c_row++;
	term->c_col = term->m_prompt_len;
	ft_setcursor(0, term->c_row);
	write(1, MINI_PROMPT, term->m_prompt_len);
	get_nl_addr(term, input);
	term->total_row++;
}

void	nl_open_qoute(t_term *term, char *input)
{
	write(1, "\n", 1);
	term->nl = 1; // I dont think has been relevant
	write(1, MINI_PROMPT, term->m_prompt_len);
	term->c_row++;
	term->c_col = term->m_prompt_len;
	term->total_row++;
	get_nl_addr(term, input);
	term->q_prompt++;
}

void	nl_terminal_size(t_term *term, char *input)
{
	// if (input[term->indx])
	// {	
	// 	ft_print_trail(term, input);
	// }
	term->c_row++;
	term->c_col = 0;
	term->m_prompt_len = 0;
	if (term->indx == term->bytes)
		get_nl_addr(term, input);
	term->total_row++;
	ft_setcursor(term->c_col, term->c_row);
}
