/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_lines.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 13:42:45 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/03 10:26:07 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/**
 * It handles the newline character
 * 
 * @param term the term structure
 * @param input the input string
 */
void	nl_backslash(t_term *term, char *input)
{
	term->c_row++;
	term->total_row++;
	term->c_col = term->m_prompt_len;
	ft_setcursor(0, term->c_row);
	write(1, MINI_PROMPT, term->m_prompt_len);
	if (term->nl_addr[term->c_row])
		insert_middle_nl_addr(term, input, term->c_row, term->indx);
	else
		get_nl_addr(term, input, term->indx);
	if (input[term->indx])
		ft_print_trail(term, input);
}

void	nl_open_qoute(t_term *term, char *input)
{
	term->c_row++;
	term->total_row++;
	term->c_col = term->m_prompt_len;
	ft_setcursor(0, term->c_row);
	write(1, MINI_PROMPT, term->m_prompt_len);
	if (term->nl_addr[term->c_row])
		insert_middle_nl_addr(term, input, term->c_row, term->indx);
	else
		get_nl_addr(term, input, term->indx);
}

/**
 * It takes a term struct, a string, a row, and a position, and inserts the string into the term
 * struct's nl_addr array at the given row and position
 * 
 * @param term the terminal structure
 * @param input the input string
 * @param row the row number where the new line is to be inserted
 * @param pos the position of the cursor in the current row
 */
void  insert_middle_nl_addr(t_term *term, char *input, size_t row, size_t pos)
{
	size_t	i;
	size_t	j;
	char 	**new_arr;
	
	i = 0;
	j = 0;
	new_arr = (char **)ft_memalloc(sizeof(char *) * (term->total_row + 2));
	while (i <= term->total_row)
	{
		if (i == row)
			new_arr[i] = &input[pos];
		else
			new_arr[i] = term->nl_addr[j++];
		i++;
	}
	new_arr[i] = NULL;
	ft_memdel((void **)&term->nl_addr);
	term->nl_addr = new_arr;
}
