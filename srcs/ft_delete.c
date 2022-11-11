/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delete.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 14:37:39 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/10 16:50:22 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

static void	update_nl_addr_del(t_term *t)
{
	size_t	row;

	row = t->c_row + 1;
	while (t->nl_addr[row])
	{
		if (ft_is_prompt_line(t, row))
			t->nl_addr[row] = &t->nl_addr[row][-1];
		row++;
	}
}

void	ft_delete(t_term *t)
{
	size_t	len;
	size_t	row;

	if (t->index
		&& (t->inp[t->index] == D_QUO || t->inp[t->index] == S_QUO))
		ft_quote_decrement(t, 0);
	row = ft_row_lowest_line(t);
	if (t->nl_addr[row + 1]
		&& (&t->inp[t->index + 1] == t->nl_addr[t->c_row + 1]
			&& ft_is_prompt_line(t, t->c_row + 1)))
		return ;
	if (t->nl_addr[row + 1])
		len = (t->nl_addr[row + 1] - t->nl_addr[row]) - 1;
	else
		len = &t->inp[t->bytes] - t->nl_addr[row];
	update_nl_addr_del(t);
	ft_deletion_shift(t, DEL);
	ft_run_capability("ce");
	if (!len)
	{
		ft_remove_nl_addr(t, row);
		t->total_row--;
	}
	if (t->inp[t->index])
		ft_print_trail(t);
}
