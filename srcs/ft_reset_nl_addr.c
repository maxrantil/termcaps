/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reset_nl_addr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:20:44 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/07 15:26:52 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/**
 * It takes a string and
 * creates an array of pointers to the beginning of each line in the string
 * 
 * @param term the term structure
 * @param input the string to be parsed
 */
void	ft_reset_nl_addr(t_term *term, char *input)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	term->total_row = 0;
	if (term->nl_addr)
		ft_memdel((void **)&term->nl_addr);
	ft_add_nl_last_row(term, input, i);
	while (input[++i])
	{
		len++;
		if (((len + ft_get_prompt_len(term, term->total_row)) + 1)
			/ (term->ws_col) || input[i] == '\n')
		{
			ft_add_nl_last_row(term, input, i + 1);
			term->total_row++;
			len = -1;
		}
		if (input[i] == D_QUO || input[i] == S_QUO)
			quote_handling(term, input[i]);
	}
}
