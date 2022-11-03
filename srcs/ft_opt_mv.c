/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_opt_mv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 09:05:53 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/03 14:25:22 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

static void	word_mv(t_term *term, char *input)
{
	if (term->ch == 98 && (&input[term->index] > term->nl_addr[term->c_row]))
		word_left(term, input);
	else if (term->ch == 102 && (term->index < term->bytes))
	{
		if (term->nl_addr[term->c_row + 1])
		{
			if (&input[term->index] < &term->nl_addr[term->c_row + 1][-1])
				word_right(term, input);
		}
		else
			word_right(term, input);
	}
}

static void	line_mv(t_term *term, char *input)
{
	term->ch = ft_get_input();
	if (term->ch == 59)
	{
		term->ch = ft_get_input();
		if (term->ch == 51)
		{
			term->ch = ft_get_input();
			if (term->ch == 65 && term->c_row)
				line_up(term);
			if (term->ch == 66 && term->c_row < term->total_row)
				line_down(input, term);
			term->ch = 0;
		}
	}
}

void	ft_opt_mv(t_term *term, char *input)
{
	if (term->ch == 98 || term->ch == 102)
		word_mv(term, input);
	else if (term->ch == 49)
		line_mv(term, input);
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
