/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_cycle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:46:24 by mrantil           #+#    #+#             */
/*   Updated: 2022/10/20 14:46:05 by mrantil          ###   ########.fr       */
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
	if (term->indx == term->c_col)
	{
		term->c_col--;
		term->indx--;
		input[term->indx] = '\0';
	}
	else
		ft_deletion_shift(input, term, BCK);
	if (input[term->indx])
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
		else if (term->ch == CTRL_D && term->indx < term->c_col)
			delete(term, input);
		else if (term->ch == BACKSPACE && term->indx > 0)
			backspace(term, input);
		if (term->ch == ESCAPE)
			esc_parse(term, input);
		if (isprint(term->ch) || (term->ch == ENTER && quote))
		{
			term->total_col++;
			ft_putc(term->ch);
			input[term->indx++] = term->ch;
			ft_setcursor(++term->c_col, term->c_row);
			if (term->c_col != term->total_col)
				ft_insertion_shift(term, input);
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
