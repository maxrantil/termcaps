/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input_cycle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:46:24 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/07 11:53:05 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

static void	ft_end_cycle(t_term *term, char *input)
{
	ft_setcursor(0, term->total_row + 1);
	vec_push(&term->v_history, input);
	if (!ft_strcmp(input, "history"))
		ft_history(term);
	ft_memdel((void **)&term->nl_addr);
	if (term->input_cpy)
		ft_strdel(&term->input_cpy);
		
}

void	ft_input_cycle(t_term *term, char *input)
{
	add_nl_last_row(term, input, 0);
	write(1, PROMPT, term->prompt_len);
	while (term->ch != -1)
	{
		term->ch = ft_get_input();
		if (term->ch == ENTER && !term->bytes)
			break ;
		if (ft_isprint(term->ch) || term->ch == ENTER)
			insertion(term, input);
		if (term->ch == ENTER)
		{
			if (term->q_qty && (term->q_qty % 2))
				create_prompt_line(term, input);
			else if ((input[term->index - 2] == '\\' && (term->index <= 2 || input[term->index - 3] != '\\')))
				create_prompt_line(term, input);
			else
			{
				ft_end_cycle(term, input);
				break ;
			}
		}
		else if (term->ch == CTRL_D && term->index < term->bytes)
			delete(term, input);
		else if (term->ch == BACKSPACE && term->index)
			backspace(term, input);
		if (term->ch == ESCAPE)
			ft_esc_parse(term, input);
		if (input[term->index])
			ft_print_trail(term, input);
		if (term->ch == -1)
			ft_putstr_fd("error, ft_get_input()\n", STDERR_FILENO);
	}
}
