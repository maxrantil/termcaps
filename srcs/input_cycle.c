/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_cycle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:46:24 by mrantil           #+#    #+#             */
/*   Updated: 2022/10/20 12:37:14 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

static void	delete(char *input, t_term *term)
{
	deletion_shift(input, term, DEL);
	clear_trail();
	print_trail(input, term);
}

static void	backspace(char *input, t_term *term)
{
	ft_cursor_left(term);
	clear_trail();
	if (term->cursor == term->bytes)
	{
		term->bytes--;
		term->cursor--;
		input[term->cursor] = '\0';
	}
	else
		deletion_shift(input, term, BCK);
	if (input[term->cursor])
		print_trail(input, term);
}

static void	char_print(char *input, t_term *term)
{
	write(1, &term->ch, 1);
	if (input[term->cursor])
		insertion_shift(input, term);
	input[term->cursor++] = term->ch;
	if (input[term->cursor])
		print_trail(input, term);
	term->bytes++;
}

static void	quote_count(int *quote, int c)
{
	if (!*quote)
		*quote = c;
	else if (*quote == c)
		*quote = 0;
}

void	input_cycle(char *input, t_term *term)
{
	int		quote;

	quote = 0;
	while (term->ch != -1)
	{
		term->ch = get_input();
		if (term->ch == D_QUOTE || term->ch == S_QUOTE)
			quote_count(&quote, term->ch);
		/* if (term->ch == KILL)
			kill_process(term->ch); */
		else if (term->ch == ENTER && !quote)
			return ;
		else if (term->ch == CTRL_D && term->cursor < term->bytes)
			delete(input, term);
		else if (term->ch == BACKSPACE && term->cursor > 0)
			backspace(input, term);
		if (term->ch == ESCAPE)
			esc_parse(input, term);
		if (isprint(term->ch) || (term->ch == ENTER && quote))
		{
			char_print(input, term);
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
