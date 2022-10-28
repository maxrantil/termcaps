/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input_cycle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:46:24 by mrantil           #+#    #+#             */
/*   Updated: 2022/10/27 14:50:59 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

void	ft_input_cycle(t_term *term, char *input)
{
	get_nl_addr(term, input);
	write(1, PROMPT, term->prompt_len);
	while (term->ch != -1)
	{	
		term->ch = ft_get_input();
		if (term->ch == D_QUOTE || term->ch == S_QUOTE)
			quote_increment(term);
		/*#########################################################*/
		if (term->ch == CTRL_C)
			break ;
		else if (term->ch == ENTER && (!(term->q_qty % 2) && input[term->indx - 1] != '\\'))
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
		/*#########################################################*/
		else if (term->ch == CTRL_D && term->indx < term->bytes)
			delete(term, input);
		else if (term->ch == BACKSPACE && term->indx)
			backspace(term, input);
		if (term->ch == ESCAPE)
			ft_esc_parse(term, input);
		if (term->ch == ENTER && input[term->indx - 1] == '\\')
			nl_backslash(term, input);
		if (isprint(term->ch) || (term->ch == ENTER && (term->q_qty % 2)))
			insertion(term, input);
		if (term->ch == -1)
			ft_putstr_fd("error, ft_get_input()\n", STDERR_FILENO);
	}
}
