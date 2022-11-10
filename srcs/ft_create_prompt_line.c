/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_prompt_line.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:40:40 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/10 12:02:25 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

void	ft_create_prompt_line(t_term *t, size_t loc)
{
	t->c_row++;
	t->total_row++;
	t->c_col = t->m_prompt_len;
	ft_putchar('\n');
	ft_setcursor(0, t->c_row + t->start_row);
	write(1, MINI_PROMPT, t->m_prompt_len);
	if (t->nl_addr[t->c_row])
		ft_add_nl_mid_row(t, t->c_row, loc);
	else
		ft_add_nl_last_row(t, loc);
}
