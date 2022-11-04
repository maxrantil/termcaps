/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history_trigger.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 10:59:10 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/04 13:58:44 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

static size_t	get_prompt_len(t_term *term, size_t row)
{
	size_t	prompt_len;

	prompt_len = 0;
	if (!row)
		prompt_len = term->prompt_len;
	else if (is_prompt_line(term, row))
		prompt_len = term->m_prompt_len;
	return (prompt_len);
}

static void	setup_nl_addr(t_term *term, char *input)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	term->total_row = 0;
	ft_memdel((void **)&term->nl_addr);
	add_nl_last_row(term, input, i);
	while (input[++i])
	{
		len++;
		if (((len + get_prompt_len(term, term->total_row)) + 1) / (term->ws_col) || input[i] == '\n')
		{
			add_nl_last_row(term, input, i + 1);
			term->total_row++;
			len = -1;
		}
		if (input[i] == D_QUO || input[i] == S_QUO)
			quote_handling(term, input[i]);
	}
}

static void	ft_history_trigger_start(t_term *term)
{
	ft_run_capability("vi");
	term->quote = 0;
	term->q_qty = 0;
	term->c_col = 0;
	term->c_row = 0;
	ft_setcursor(term->c_col, term->c_row);
	ft_run_capability("cd");
	ft_putstr(PROMPT);
}

static void	ft_history_trigger_end(t_term *term, char *input)
{
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
	ft_run_capability("ve");
}

static void nl_addr_cpy(t_term *term)
{
	size_t i;

	i = -1;
	term->total_row_cpy = term->total_row;
	term->nl_addr_cpy = (char **)ft_memalloc(sizeof(char *) * (term->total_row + 2));
	while (term->nl_addr[++i])
		term->nl_addr_cpy[i] = term->nl_addr[i];
	term->nl_addr_cpy[i] = NULL;
}

void	ft_history_trigger(t_term *term, char *input, int his)
{
	char	*history;

	ft_history_trigger_start(term);
	history = (char *)vec_get(&term->v_history, term->v_history.len - his);
	if (history)
	{
		nl_addr_cpy(term);
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
		ft_memdel((void **)&term->nl_addr);
		term->nl_addr = term->nl_addr_cpy;
		term->nl_addr_cpy = NULL;
		term->total_row = term->total_row_cpy;
		ft_strdel(&term->input_cpy);
	}
	ft_print_trail(term, input);
	ft_history_trigger_end(term, input);
}
