/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_prompt_line.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:40:40 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/09 10:05:36 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/**
 * It creates a new line for the prompt
 *
 * @param term the term struct
 * @param term->inp the term->inp string
 */
void	ft_create_prompt_line(t_term *term, size_t loc)
{
	term->c_row++;
	term->total_row++;
	term->c_col = term->m_prompt_len;
	ft_setcursor(0, term->c_row);
	write(1, MINI_PROMPT, term->m_prompt_len);
	if (term->nl_addr[term->c_row])
		ft_add_nl_mid_row(term, term->c_row, loc);
	else
		ft_add_nl_last_row(term, loc);
}
