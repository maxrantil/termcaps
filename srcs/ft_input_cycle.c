/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input_cycle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:46:24 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/03 15:40:43 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

void	ft_input_cycle(t_term *term, char *input)
{
	add_nl_last_row(term, input, 0);
	write(1, PROMPT, term->prompt_len);
	while (term->ch != -1)
	{
		term->ch = ft_get_input();
		if (term->ch == D_QUO || term->ch == S_QUO)
			quote_open(term);
		/*#########################################################*/
		if (term->ch == CTRL_C)
		{
			char **str;

			ft_setcursor(0, term->ws_row - 1);
			ft_run_capability("ce");
			ft_putchar('[');
			ft_putnbr(term->c_row);
			ft_putchar(']');
			if (is_prompt_line(term, term->c_row))
				ft_putstr("{1}");
			else
				ft_putstr("{0}");
			str = term->nl_addr;
			while (*str)
			{
				ft_putchar('[');
				if (**str == '\n')
				{
					ft_putchar('\\');
					ft_putchar('n');
				}
				else
					ft_putchar(**str);
				ft_putchar(']');
				str++;
			}
			ft_setcursor(term->c_col, term->c_row);
		}
		else if (term->ch == ENTER && (!(term->q_qty % 2) && input[term->index - 1] != '\\'))
		{
			ft_setcursor(0, term->total_row + 1);
			vec_push(&term->v_history, input);
			if (!ft_strcmp(input, "history"))
				ft_history(term);
			ft_memdel((void **)&term->nl_addr);
			break ;
		}
		/*#########################################################*/
		else if (term->ch == CTRL_D && term->index < term->bytes)
			delete(term, input);
		else if (term->ch == BACKSPACE && term->index)
			backspace(term, input);
		if (term->ch == ESCAPE)
			ft_esc_parse(term, input);
		if (term->ch == ENTER && input[term->index - 1] == '\\' && !(term->q_qty % 2))
			create_prompt_line(term, input);
		if (isprint(term->ch) || (term->ch == ENTER && (term->q_qty % 2)))
			insertion(term, input);
		if (input[term->index])
			ft_print_trail(term, input);
		if (term->ch == -1)
			ft_putstr_fd("error, ft_get_input()\n", STDERR_FILENO);
	}
}
