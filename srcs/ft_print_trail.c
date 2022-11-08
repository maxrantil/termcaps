/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_trail.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 14:40:06 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/08 12:51:34 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/**
 * It prints the prompt
 * 
 * @param row the row of the cursor
 */
static void	ft_print_prompt(size_t row)
{
	if (!row)
		ft_putstr(PROMPT);
	else
		ft_putstr(MINI_PROMPT);
}

/**
 * It prints the line trail
 * 
 * @param term the t_term struct
 * @param input the input string
 */
static void	ft_print_line_trail(t_term *term, char *input)
{
	size_t	row;
	char	*new_line;

	new_line = NULL;
	row = 0;
	ft_setcursor(0, row);
	// ft_run_capability("cd");
	while (row <= term->total_row)
	{
		if (ft_is_prompt_line(term, row))
			ft_print_prompt(row);
		new_line = term->nl_addr[row];
		if (*new_line == '\n')
			new_line++;
		if (term->nl_addr[row + 1])
			write(1, new_line, term->nl_addr[row + 1] - new_line);
		else
			write(1, new_line, &input[term->bytes] - new_line);
		ft_setcursor(0, ++row);
	}
}

/**
 * It prints the line trail
 * 
 * @param term the term structure
 * @param input the string to be printed
 */
void	ft_print_trail(t_term *term, char *input)
{
	ft_run_capability("vi");
	ft_print_line_trail(term, input);
	ft_setcursor(term->c_col, term->c_row);
	ft_run_capability("ve");
}
