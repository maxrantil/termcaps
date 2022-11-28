/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_line_up.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:24:39 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/28 12:37:14 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

static void	ft_move_up_end_line(t_term *t, ssize_t len, ssize_t prompt_len)
{
	t->c_col = (len + prompt_len) - 1;
	t->index = (t->nl_addr[t->c_row] - t->nl_addr[0]) - 1;
}

static void	ft_move_up(t_term *t, ssize_t prompt_len)
{
	if (t->c_col < prompt_len)
	{
		t->c_col = prompt_len;
		if (t->c_row == 1)
			t->index = 0;
		else
			t->index = t->nl_addr[t->c_row - 1] - t->nl_addr[0];
	}
	else
		t->index = (&t->nl_addr[t->c_row - 1]
			[t->c_col - prompt_len] - t->nl_addr[0]);
}

void	ft_line_up(t_term *t)
{
	ssize_t	len;
	ssize_t	prompt_len;

	len = t->nl_addr[t->c_row] - t->nl_addr[t->c_row - 1];
	prompt_len = ft_mv_prompt_len(t, -1);
	if (t->c_col < (len + prompt_len))
		ft_move_up(t, prompt_len);
	else
		ft_move_up_end_line(t, len, prompt_len);
	t->c_row--;
	ft_setcursor(t->c_col, (ft_get_linenbr() - 1));
}
