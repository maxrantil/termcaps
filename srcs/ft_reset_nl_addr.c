/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reset_nl_addr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:20:44 by mrantil           #+#    #+#             */
/*   Updated: 2022/12/08 18:52:35 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/*
 * It takes the input string and creates an array of pointers to the
 * beginning of each line
 *
 * @param t the term structure
 */
void	ft_reset_nl_addr(t_term *t)
{
	ssize_t	i;
	ssize_t	len;

	i = -1;
	len = 0;
	t->total_row = 0;
	if (t->nl_addr)
		ft_memdel((void **)&t->nl_addr);
	ft_add_nl_last_row(t, t->inp, 0);
	while (t->inp[++i])
	{
		len++;
		if (((len + ft_get_prompt_len(t, t->total_row))) == t->ws_col \
			|| t->inp[i] == '\n')
		{
			ft_add_nl_last_row(t, t->inp, i + 1);
			t->total_row++;
			len = 0;
		}
		if (t->inp[i] == D_QUO || t->inp[i] == S_QUO)
			ft_quote_handling(t, t->inp[i]);
	}
}
