/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_cycle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:46:24 by mrantil           #+#    #+#             */
/*   Updated: 2022/10/20 16:25:31 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

static void	delete(t_term *term, char *input)
{
	ft_deletion_shift(input, term, DEL);
	ft_clear_trail();
	ft_print_trail(term, input);
}

static void	backspace(t_term *term, char *input)
{
	write(1, "\033[1D", 4);
	ft_clear_trail();
	if (term->bytes == term->c_col)
	{
		term->c_col--;
		term->bytes--;
		input[term->bytes] = '\0';
	}
	else
		ft_deletion_shift(input, term, BCK);
	if (input[term->bytes])
		ft_print_trail(term, input);
}

static void	quote_count(int *quote, int c)
{
	if (!*quote)
		*quote = c;
	else if (*quote == c)
		*quote = 0;
}

void	input_cycle(t_term *term, char *input)
{
	int		quote;

	quote = 0;
	while (term->ch != -1)
	{
		term->ch = get_input();
		if (term->ch == D_QUOTE || term->ch == S_QUOTE)
			quote_count(&quote, term->ch);
		if (term->ch == CTRL_C)
			break ;
		else if (term->ch == ENTER && !quote)
			return ;
		else if (term->ch == CTRL_D && term->bytes < term->c_col)
			delete(term, input);
		else if (term->ch == BACKSPACE && term->bytes > 0)
			backspace(term, input);
		if (term->ch == ESCAPE)
			esc_parse(term, input);
		if (isprint(term->ch) || (term->ch == ENTER && quote))
		{
			ft_putc(term->ch);
			if (input[term->c_col])
				ft_insertion_shift(term, input);
			input[term->c_col++] = term->ch;
			term->total_col++;
			ft_setcursor(term->c_col, term->c_row);
			if (input[term->c_col])
				ft_print_trail(term, input);
			term->bytes++;
			if (term->ch == ENTER && quote)
			{
				write(1, "> ", 2);
				term->c_row++; 
				term->total_row++;
			}
		}
		if (term->ch == -1)
			ft_putstr_fd("error, get_input()\n", STDERR_FILENO);
	}
}
