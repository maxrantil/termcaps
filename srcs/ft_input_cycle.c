/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input_cycle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:46:24 by mrantil           #+#    #+#             */
/*   Updated: 2022/10/25 14:47:21 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

static void	delete(t_term *term, char *input)
{
	ft_deletion_shift(input, term, DEL);
	ft_run_capability("ce");
	ft_print_trail(term, input);
}

static void	backspace(t_term *term, char *input)
{
	if (&input[term->indx] == term->new_line_addr[term->c_row])
	{
		term->c_col = term->new_line_addr[term->c_row] - term->new_line_addr[term->c_row - 1];
		term->c_row--;
		if (!term->c_row)
			term->c_col += 3;
		else
			term->c_col += 2;
	}
	ft_setcursor(--term->c_col, term->c_row);
	ft_run_capability("ce");
	if ((int)term->indx == term->bytes)
	{
		input[--term->bytes] = '\0';
		term->indx--;
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

static void	get_new_line_addr(char *input, t_term *term)
{
	int		index;
	char	**fresh_array;

	index = -1;
	fresh_array = NULL;
	if (!term->new_line_addr)
	{
		term->new_line_addr = (char **)ft_memalloc(sizeof(char *) * 2);
		term->new_line_addr[0] = &input[term->indx];
		term->new_line_addr[1] = NULL;
	}
	else
	{
		fresh_array = (char **)ft_memalloc(sizeof(char *) * (term->total_row + 2));
		while (term->new_line_addr[++index])
			fresh_array[index] = term->new_line_addr[index];
		fresh_array[index++] = &input[term->indx];
		fresh_array[index] = NULL;
		ft_memdel((void **)&term->new_line_addr);
		term->new_line_addr = fresh_array;
	}
}

static void update_nl_addr(char *input, t_term *term, int num)
{
	int		i;

	if (term->new_line_addr[term->c_row + 1])
	{	
		i = term->c_row + 1;
		while (i <= term->total_row)
		{
			term->new_line_addr[i] = &term->new_line_addr[i][num];
			i++;	
		}
	}
	if (!term->indx)
		term->new_line_addr[0] = &input[0];
}

void	ft_input_cycle(t_term *term, char *input)
{
	int		quote;

	quote = 0;
	write(1, "$> ", 3);
	while (term->ch != -1)
	{	
		term->ch = ft_get_input();
		if (!term->new_line_addr) // getting address of beginning
			get_new_line_addr(input, term);
		if (term->ch == D_QUOTE || term->ch == S_QUOTE)
			quote_count(&quote, term->ch);
		if (term->ch == CTRL_C)
			break ;
		else if (term->ch == ENTER && !quote)
		{
			ft_putchar('\n');
			ft_putstr(input);
			ft_putchar('\n');
			ft_putendl_fd(input, STDOUT_FILENO);
			write(1, "$> ", 3);
			term->c_col = 3;
			term->total_row += term->q_prompt + 2;
			// term->c_row += term->q_prompt + 2;
			term->indx = 0;
			vec_push(&term->v_history, input);
			if (!ft_strcmp(input, "history"))
				ft_history(term);
			ft_memset(input, '\0', BUFFSIZE);
			ft_memdel((void **)&term->new_line_addr);
			// break ;
		}
		else if (term->ch == CTRL_D && (int)term->indx < term->bytes)
		{
			delete(term, input);
			update_nl_addr(input, term, -1);
		}
		else if (term->ch == BACKSPACE && term->indx)
		{
			backspace(term, input);
			update_nl_addr(input, term, -1);
		}
		if (term->ch == ESCAPE)
			ft_esc_parse(term, input);
		if (isprint(term->ch) || (term->ch == ENTER && quote))
		{
			ft_putc(term->ch);
			update_nl_addr(input, term, 1);
			if (input[term->indx])
				ft_insertion_shift(term, input);
			input[term->indx++] = term->ch;
			term->total_col++;
			ft_setcursor(++term->c_col, term->c_row);
			if (input[term->indx])
				ft_print_trail(term, input);
			term->bytes++;
			if (term->ch == ENTER && quote)
			{
				write(1, "\n> ", 3);
				term->c_row++; 
				term->c_col = 2;
				term->total_row++;
				get_new_line_addr(input, term);
				term->q_prompt++;
			}
			if (term->c_col == (int)term->ws_col - 1) // not sure if it should be - 1;
			{
				get_new_line_addr(input, term);
				term->c_row++; 
				term->c_col = -1;
				term->total_row++;
			}
		}
		if (term->ch == -1)
			ft_putstr_fd("error, ft_get_input()\n", STDERR_FILENO);
	}
}
