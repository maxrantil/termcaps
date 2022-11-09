/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_prompt_line.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:40:40 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/09 10:15:45 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

void	ft_create_prompt_line(t_term *t, size_t loc)
{
	t->c_row++;
	t->total_row++;
	t->c_col = t->m_prompt_len;
	ft_setcursor(0, t->c_row);
	write(1, MINI_PROMPT, t->m_prompt_len);
	if (t->nl_addr[t->c_row])
		ft_add_nl_mid_row(t, t->c_row, loc);
	else
		ft_add_nl_last_row(t, loc);
}
