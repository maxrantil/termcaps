/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_prompt_line.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:40:40 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/11 15:45:30 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

void	ft_create_prompt_line(t_term *t, ssize_t loc)
{
	t->c_row++;
	t->total_row++;
	t->c_col = t->m_prompt_len;
	ft_putchar('\n');
	ft_setcursor(0, ft_display_row_v2(t, t->c_row));
	write(1, MINI_PROMPT, (size_t)t->m_prompt_len);
	ft_add_nl_last_row(t, loc);
}
