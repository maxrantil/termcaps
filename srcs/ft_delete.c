/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delete.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 14:37:39 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/07 16:17:07 by mrantil          ###   ########.fr       */
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

/* static void	update_nl_addr(char *input, t_term *term, int num)
{
	size_t		i;

	if (term->nl_addr[term->c_row + 1])
	{	
		i = term->c_row;
		while (++i <= term->total_row)
			term->nl_addr[i] = &term->nl_addr[i][num];
	}
	if (!term->index)
		term->nl_addr[0] = &input[0];
} */

/**
 * If the quote quantity is even, then the quote is set to the current character 
 * and the quote quantity is decremented. 
 * 
 * If the quote quantity is odd and the quote is equal to the current character,
 * then the quote is set to 0 and the quote quantity is decremented.
 * 
 * @param input the string that is being parsed
 * @param term the structure that contains all the information about the 
 * current state of the terminal.
 */
static void	ft_quote_decremented(char *input, t_term *term)
{
	if (!(term->q_qty % 2))
	{	
		term->quote = input[term->index];
		term->q_qty--;
	}
	else if ((term->q_qty % 2) && term->quote == input[term->index])
	{
		term->quote = 0;
		term->q_qty--;
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
		ft_quote_decremented(input, term);
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
