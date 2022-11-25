/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insertion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 07:56:09 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/25 13:22:32 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

void ft_delim_fetch(t_term *t)
{
	char	*ptr;
	char	*end_q;

	ptr = NULL;
	if (t->heredoc && !t->delim)
	{
		ptr = ft_strchr(t->inp, '<') + 2;
		while (*ptr && ft_isspace(ptr))
			ptr++;
		if (*ptr)
		{
			end_q = ptr;
			while (*end_q && !ft_isspace(end_q))
				end_q++;
			t->delim = ft_strsub(ptr, 0, end_q - ptr);
		}
	}
}

void	ft_insertion(t_term *t)
{
	if (t->ch == ENTER)
	{
		if (!t->nl_addr[t->c_row + 1])
		{
			if (t->bslash || t->q_qty % 2 || (t->heredoc && ft_strcmp(t->nl_addr[t->c_row], t->delim)))
			{
				t->inp[t->bytes++] = (char)t->ch;
				ft_create_prompt_line(t, t->bytes);
				t->index = t->bytes;
			}
		}
		ft_delim_fetch(t);
	}
	else
	{
		ft_putc(t->ch);
		ft_heredoc_handling(t);
		ft_bslash_handling(t);
		if ((t->ch == D_QUO || t->ch == S_QUO) && !t->heredoc)
		{
			if (!t->bslash)
				ft_quote_handling(t, (char)t->ch);
			else
				t->bslash = 0;
		}
		t->c_col++;
		ft_shift_nl_addr(t, 1);
		if (t->inp[t->index])
			ft_shift_insert(t);
		t->inp[t->index++] = (char)t->ch;
		t->bytes++;
	}
	ft_trigger_nl(t);
	if (t->inp[t->index])
		ft_print_trail(t);
}
