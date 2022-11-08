/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input_cycle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:46:24 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/08 17:55:01 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/**
 * This function is called at the end of the main loop. It sets the cursor
 * to the bottom of the screen, pushes the input to the history vector,
 * and frees the newline address
 *
 * @param term the term struct
 * @param input the string that the user has typed in
 */
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

void ft_restart_cycle(t_term *t, char *input)
{
	ft_putendl_fd(input, STDOUT_FILENO);
	ft_memset(input, '\0', BUFFSIZE);
	t->quote = 0;
	t->q_qty = 0;
	t->bytes = 0;
	t->index = 0;
	t->c_col = t->prompt_len;
	t->total_row += 2;
	t->c_row = t->total_row;
	// printf("NUM OF LINE SIN MEM %d\n", tgetnum("lm"));
	// printf("NUM OF LINE SIN MEM %zu\n", t->ws_row);
}
/**
 * It's a loop that reads input from the terminal, and then does
 * something with it
 *
 * @param term a pointer to the t_term struct
 * @param input the string that will be edited
 */
void	ft_input_cycle(t_term *term, char *input) //more then 25 lines!
{
	ft_add_nl_last_row(term, input, 0);
	write(1, PROMPT, term->prompt_len);
	while (term->ch != -1)
	{
		term->ch = ft_get_input();
		if (ft_isprint(term->ch) || term->ch == ENTER)
			ft_insertion(term, input);
		if (term->ch == ENTER)
		{
			if (input[term->bytes - 2] != '\\' && !(term->q_qty % 2))
			{
				ft_end_cycle(term, input);
				ft_restart_cycle(term, input);
				ft_add_nl_last_row(term, input, 0);
				write(1, PROMPT, term->prompt_len);
				ft_setcursor(term->c_col, term->c_row);
				continue;
			}
		}
		else if (term->ch == CTRL_D && term->index < term->bytes)
			ft_delete(term, input);
		else if (term->ch == CTRL_C)
			break ;
		else if (term->ch == BACKSPACE && term->index)
			ft_backspace(term, input);
		if (term->ch == ESCAPE)
			ft_esc_parse(term, input);
		if (input[term->index])
			ft_print_trail(term, input);
		if (term->ch == -1)
			ft_putstr_fd("error, ft_get_input()\n", STDERR_FILENO);
	}
}
