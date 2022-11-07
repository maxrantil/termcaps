/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_word_mv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:43:30 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/07 16:20:10 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/**
 * It moves the cursor to the beginning of the previous word
 * 
 * @param term the terminal structure
 * @param input the string that the user is editing
 */
static void	ft_word_left(t_term *term, char *input)
{
	while (term->index && ft_isspace(&input[term->index - 1]))
	{
		if (&input[term->index + 1] == term->nl_addr[term->c_row])
			break ;
		term->index--;
	}
	while (term->index && !ft_isspace(&input[term->index - 1]))
	{
		if (&input[term->index] == term->nl_addr[term->c_row])
			break ;
		term->index--;
	}
	term->c_col = &input[term->index] - term->nl_addr[term->c_row];
	if (term->nl_addr[term->c_row] == &input[0])
		term->c_col += term->prompt_len;
	else if (ft_is_prompt_line(term, term->c_row))
		term->c_col += term->m_prompt_len;
	ft_setcursor(term->c_col, term->c_row);
}

/**
 * It moves the cursor to the next word
 * 
 * @param term the terminal structure
 * @param input the string of characters that the user has typed in
 */
static void	ft_word_right(t_term *term, char *input)
{
	size_t	row;

	row = term->c_row + 1;
	while (term->index < term->bytes && ft_isspace(&input[term->index]))
	{
		if (term->nl_addr[row] \
		&& &input[term->index + 1] == term->nl_addr[row])
			break ;
		term->index++;
	}
	while (term->index < term->bytes && !ft_isspace(&input[term->index]))
	{
		if (term->nl_addr[row] \
		&& &input[term->index + 1] == term->nl_addr[row])
			break ;
		term->index++;
	}
	term->c_col = &input[term->index] - term->nl_addr[row - 1];
	if (term->nl_addr[row - 1] == &input[0])
		term->c_col += term->prompt_len;
	else if (ft_is_prompt_line(term, row - 1))
		term->c_col += term->m_prompt_len;
	ft_setcursor(term->c_col, row - 1);
}

/**
 * If the user presses the left arrow key, move the cursor to 
 * the left until it reaches the beginning of the word. If the 
 * user presses the right arrow key, move the cursor to the
 * right until it reaches the end of the word
 * 
 * @param term the struct that holds all the information about the terminal
 * @param input the string of characters that the user has typed in
 */
void	ft_word_mv(t_term *term, char *input)
{
	if (term->ch == 98 && (&input[term->index] > term->nl_addr[term->c_row]))
		ft_word_left(term, input);
	else if (term->ch == 102 && (term->index < term->bytes))
	{
		if (term->nl_addr[term->c_row + 1])
		{
			if (&input[term->index] < &term->nl_addr[term->c_row + 1][-1])
				ft_word_right(term, input);
		}
		else
			ft_word_right(term, input);
	}
}
