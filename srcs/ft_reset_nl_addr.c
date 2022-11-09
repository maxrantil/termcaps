/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reset_nl_addr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:20:44 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/09 10:10:32 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

void	ft_reset_nl_addr(t_term *term)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	term->total_row = 0;
	if (term->nl_addr)
		ft_memdel((void **)&term->nl_addr);
	ft_add_nl_last_row(term, i);
	while (term->inp[++i])
	{
		len++;
		if (((len + ft_get_prompt_len(term, term->total_row)) + 1)
			/ (term->ws_col) || term->inp[i] == '\n')
		{
			ft_add_nl_last_row(term, i + 1);
			term->total_row++;
			len = -1;
		}
		if (term->inp[i] == D_QUO || term->inp[i] == S_QUO)
			ft_quote_handling(term, term->inp[i]);
	}
}
