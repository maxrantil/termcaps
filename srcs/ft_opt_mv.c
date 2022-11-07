/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_opt_mv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 09:05:53 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/07 16:18:18 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/**
 * It moves the cursor to the beginning or end of the line, or to the
 * beginning or end of the word
 * 
 * @param term the term struct
 * @param input the string that the user is editing
 */
void	ft_opt_mv(t_term *term, char *input)
{
	if (term->ch == 98 || term->ch == 102)
		ft_word_mv(term, input);
	else if (term->ch == 49)
		ft_line_mv(term, input);
}

// void	ft_alt_cursor_mv(t_term *term, char *input)
// {
// 	if (term->ch == 98 && &input[term->index] > term->nl_addr[term->c_row])
// 		word_left(term, input);
// 	else if (term->ch == 102 && term->index < term->bytes)
// 	{
// 		if (term->nl_addr[term->c_row + 1])
// 		{
// 			if (&input[term->index] < &term->nl_addr[term->c_row + 1][-1])
// 				word_right(term, input);
// 		}
// 		else
// 			word_right(term, input);
// 	}
// 	else if (term->ch == 49)
// 	{
// 		term->ch = ft_get_input();
// 		if (term->ch == 59)
// 		{
// 			term->ch = ft_get_input();
// 			if (term->ch == 51)
// 			{
// 				term->ch = ft_get_input();
// 				if (term->ch == 65 && term->c_row)
// 					line_up(term);
// 				if (term->ch == 66 && term->c_row < term->total_row)
// 					line_down(input, term);
// 				term->ch = 0;
// 			}
// 		}
// 	}
// }
