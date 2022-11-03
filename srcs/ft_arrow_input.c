/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrow_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:27:59 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/03 16:04:44 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

static void	ft_right(char *input, t_term *term)
{
	if (term->index < term->bytes)
	{
		if (term->nl_addr[term->c_row + 1])
		{
			if (&input[term->index] < (term->nl_addr[term->c_row + 1] - 1))
			{
				term->index++;
				ft_setcursor(++term->c_col, term->c_row);
			}
		}
		else
		{
			term->index++;
			ft_setcursor(++term->c_col, term->c_row);
		}
	}
}

static void	ft_left(char *input, t_term *term)
{
	term->index--;
	term->c_col--;
	if (&input[term->index + 1] == term->nl_addr[term->c_row])
	{
		if (term->c_row == 1)
			term->c_col = term->m_prompt_len;
		else
			term->c_col = term->prompt_len;
		term->c_col += (term->nl_addr[term->c_row]
				- term->nl_addr[--term->c_row]);
	}
	ft_setcursor(term->c_col, term->c_row);
}

static void	setup_nl_addr(t_term *term, char *input)
{
	size_t	i;
	size_t	len;
	size_t	prompt_len;

	i = 0;
	len = 0;
	term->total_row = 0;
	ft_memdel((void **)&term->nl_addr);
	add_nl_last_row(term, input, i);
	while (input[++i])
	{
		len++;
		prompt_len = 0;
		if (!term->total_row)
			prompt_len = term->prompt_len;
		else if (is_prompt_line(term, term->total_row))
			prompt_len = term->m_prompt_len;
		if ((len + prompt_len) / (term->ws_col) || input[i] == '\n')
		{
			add_nl_last_row(term, input, i + 1);
			term->total_row++;
			len = 0;
		}
	}
}

static void	ft_history_trigger(t_term *term, char *input, int his)
{
	char *history;

	history = NULL;
	term->c_col = 0;
	term->c_row = 0;
	ft_setcursor(term->c_col, term->c_row);
	ft_run_capability("cd");
	ft_putstr(PROMPT);
	history = (char *)vec_get(&term->v_history, term->v_history.len - his);
	if (history)
	{
		term->bytes = ft_strlen(history);
		term->input_cpy = ft_strdup(input);
		ft_memset((void *)input, '\0', BUFF_SIZE);
		ft_memcpy((void *)input, (void *)history, term->bytes);
		setup_nl_addr(term, input);
	}
	else
	{
		term->bytes = ft_strlen(term->input_cpy);
		ft_memset((void *)input, '\0', BUFF_SIZE);
		ft_memcpy((void *)input, (void *)term->input_cpy, term->bytes);	
		ft_strdel(&term->input_cpy);
		setup_nl_addr(term, input);
	}
	ft_print_trail(term, input);
	term->index = term->bytes;
	term->c_row = term->total_row;
	if (is_prompt_line(term, term->c_row))
	{
		if (!term->c_row)
			term->c_col = term->prompt_len;
		else
			term->c_col = term->m_prompt_len;
	}
	term->c_col += &input[term->bytes] - term->nl_addr[term->c_row];
	ft_setcursor(term->c_col, term->total_row);
}

void	ft_arrow_input(t_term *term, char *input)
{
	static size_t	his;

	if (term->ch == 'D' && term->index)
		ft_left(input, term);
	else if (term->ch == 'C')
		ft_right(input, term);
	else if (term->ch == 'A' && his < term->v_history.len)
		ft_history_trigger(term, input, ++his);
	else if (term->ch == 'B' && his > 0)
		ft_history_trigger(term, input, --his);
}
