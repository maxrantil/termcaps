/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delete.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 14:37:39 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/08 13:56:20 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

static void	update_nl_addr_del(t_term *term)
{
	size_t	row;

	row = term->c_row + 1;
	while (term->nl_addr[row])
	{
		if (ft_is_prompt_line(term, row))
			term->nl_addr[row] = &term->nl_addr[row][-1];
		row++;
	}
}

/**
 * It deletes the character at the current cursor position
 * 
 * @param term the term struct
 * @param input the string that the user is typing
 * 
 * @return the address of the first character of the
 * 		line that is the lowest line on the screen.
 */
void	ft_delete(t_term *term, char *input)
{
	size_t	len;
	size_t	row;

	if (term->index
		&& (input[term->index] == D_QUO || input[term->index] == S_QUO))
		ft_quote_decrement(input, term, 0);
	row = ft_row_lowest_line(term);
	if (term->nl_addr[row + 1]
		&& (&input[term->index + 1] == term->nl_addr[term->c_row + 1]
			&& ft_is_prompt_line(term, term->c_row + 1)))
		return ;
	if (term->nl_addr[row + 1])
		len = (term->nl_addr[row + 1] - term->nl_addr[row]) - 1;
	else
		len = &input[term->bytes] - term->nl_addr[row];
	update_nl_addr_del(term);
	ft_deletion_shift(input, term, DEL);
	ft_run_capability("ce");
	if (!len)
	{
		ft_remove_nl_addr(term, row);
		term->total_row--;
	}
}
