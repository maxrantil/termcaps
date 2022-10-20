/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_cycle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:46:24 by mrantil           #+#    #+#             */
/*   Updated: 2022/10/20 13:38:51 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

static void	delete(t_term *term, char *input)
{
	deletion_shift(input, term, DEL);
	clear_trail();
	print_trail(term, input);
}

static void	backspace(t_term *term, char *input)
{
	ft_cursor_left(term);
	clear_trail();
	if (term->cursor == term->col)
	{
		term->col--;
		term->cursor--;
		input[term->cursor] = '\0';
	}
	else
		deletion_shift(input, term, BCK);
	if (input[term->cursor])
		print_trail(term, input);
}

static void	char_print(t_term *term, char *input)
{
	write(1, &term->ch, 1);
	if (input[term->cursor])
		insertion_shift(term, input);
	input[term->cursor++] = term->ch;
	if (input[term->cursor])
		print_trail(term, input);
	term->col++;
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
		else if (term->ch == CTRL_D && term->cursor < term->col)
			delete(term, input);
		else if (term->ch == BACKSPACE && term->cursor > 0)
			backspace(term, input);
		if (term->ch == ESCAPE)
			esc_parse(term, input);
		if (isprint(term->ch) || (term->ch == ENTER && quote))
		{
			char_print(term, input);
			if (term->ch == ENTER && quote)
			{
				write(1, "> ", 2);
				term->row++; 
				term->cur_row++;

			}
		}
		if (term->ch == -1)
			ft_putstr_fd("error, read\n", STDERR_FILENO);
	}
}
