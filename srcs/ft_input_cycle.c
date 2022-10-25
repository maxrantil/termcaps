/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input_cycle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:46:24 by mrantil           #+#    #+#             */
/*   Updated: 2022/10/25 16:31:48 by mbarutel         ###   ########.fr       */
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
	if (&input[term->indx] == term->nl_addr[term->c_row])
	{
		term->c_col = term->nl_addr[term->c_row] - term->nl_addr[term->c_row - 1];
		term->c_row--;
		if (!term->c_row)
			term->c_col += 3;
		else
			term->c_col += 2;
	}
	ft_setcursor(--term->c_col, term->c_row);
	ft_run_capability("ce");
	if (term->indx == term->bytes)
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

static void	get_nl_addr(char *input, t_term *term)
{
	int		index;
	char	**fresh_array;

	index = -1;
	fresh_array = NULL;
	if (!term->nl_addr)
	{
		term->nl_addr = (char **)ft_memalloc(sizeof(char *) * 2);
		term->nl_addr[0] = &input[term->indx];
		term->nl_addr[1] = NULL;
	}
	else
	{
		fresh_array = (char **)ft_memalloc(sizeof(char *) * (term->total_row + 2));
		while (term->nl_addr[++index])
			fresh_array[index] = term->nl_addr[index];
		fresh_array[index++] = &input[term->indx];
		fresh_array[index] = NULL;
		ft_memdel((void **)&term->nl_addr);
		term->nl_addr = fresh_array;
	}
}

static void update_nl_addr(char *input, t_term *term, int num)
{
	size_t	i;

	if (term->nl_addr[term->c_row + 1])
	{	
		i = term->c_row + 1;
		while (i <= term->total_row)
		{
			term->nl_addr[i] = &term->nl_addr[i][num];
			i++;	
		}
	}
	if (!term->indx)
		term->nl_addr[0] = &input[0];
}

void	ft_input_cycle(t_term *term, char *input)
{
	int		quote;

	quote = 0;
	get_nl_addr(input, term);
	write(1, PROMPT, term->prompt_len);
	while (term->ch != -1)
	{	
		term->ch = ft_get_input();
		if (term->ch == D_QUOTE || term->ch == S_QUOTE)
			quote_count(&quote, term->ch);
		if (term->ch == CTRL_C)
			break ;
		else if (term->ch == ENTER && !quote)
		{
			ft_putchar('\n');
			ft_putendl_fd(input, STDOUT_FILENO);
			write(1, PROMPT, term->prompt_len);
			term->c_col = ft_strlen(PROMPT);
			term->total_row += term->q_prompt + 2;
			// term->c_row += term->q_prompt + 2;
			term->indx = 0;
			vec_push(&term->v_history, input);
			if (!ft_strcmp(input, "history"))
				ft_history(term);
			ft_memset(input, '\0', BUFFSIZE);
			ft_memdel((void **)&term->nl_addr);
		}
		else if (term->ch == CTRL_D && term->indx < term->bytes)
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
			// term->total_col++; // Is this needed?
			ft_setcursor(++term->c_col, term->c_row);
			if (input[term->indx])
				ft_print_trail(term, input);
			term->bytes++;
			if (term->ch == ENTER && quote)
			{
				write(1, "\n", 1);
				write(1, MINI_PROMPT, term->m_prompt_len);
				term->c_row++; 
				term->c_col = term->m_prompt_len;
				term->total_row++;
				get_nl_addr(input, term);
				term->q_prompt++;
			}
			// if (term->c_col == term->ws_col - 1) // not sure if it should be - 1;
			// {
			// 	get_nl_addr(input, term);
			// 	term->c_row++; 
			// 	term->c_col = -1;
			// 	term->total_row++;
			// }
		}
		if (term->ch == -1)
			ft_putstr_fd("error, ft_get_input()\n", STDERR_FILENO);
	}
}
