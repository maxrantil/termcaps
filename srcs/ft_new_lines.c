/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_lines.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 13:42:45 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/31 18:13:08 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

void	nl_backslash(t_term *term, char *input)
{
	term->c_row++;
	term->c_col = term->m_prompt_len;
	ft_setcursor(0, term->c_row);
	write(1, MINI_PROMPT, term->m_prompt_len);
	get_nl_addr(term, input, term->indx);
	term->total_row++;
}

void	nl_open_qoute(t_term *term, char *input)
{
	term->c_row++;
	term->c_col = term->m_prompt_len;
	ft_setcursor(0, term->c_row);
	write(1, MINI_PROMPT, term->m_prompt_len);
	get_nl_addr(term, input, term->indx);
	term->total_row++;
}

void insert_middle_nl_addr(t_term *term, char *input, size_t row, size_t pos)
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

// void	nl_terminal_size(t_term *term, char *input)
// {
// 	term->c_col = 0;

// 	term->c_row++;
// 	if (term->nl_addr[term->c_row])
// 	{
// 		if (term->nl_addr[term->c_row][-1] == '\n' || term->nl_addr[term->c_row][-1] == '\\')
// 		{
// 			term->total_row++;
// 			insert_middle_nl_addr(term, input, term->c_row, term->indx);
// 			ft_print_trail(term, input);
// 		}
// 	}
// 	if (term->indx == term->bytes)
// 	{
// 		get_nl_addr(term, input);
// 		term->total_row++;
// 	}
// 	ft_setcursor(term->c_col, term->c_row);
// }
