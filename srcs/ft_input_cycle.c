/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input_cycle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:46:24 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/22 11:57:04 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

static void	ft_end_cycle(t_term *t)
{
	if (t->bytes)
	{
		ft_putchar('\n');
		vec_push(&t->v_history, t->inp);
	}
	if (!ft_strncmp(t->inp, "history", 7))
		ft_history(t);
	ft_memdel((void **)&t->nl_addr);
	if (t->input_cpy)
		ft_strdel(&t->input_cpy);
}

void	ft_input_cycle(t_term *t)
{
	ft_add_nl_last_row(t, 0);
	write(1, PROMPT, (size_t)t->prompt_len);
	while (t->ch != -1)
	{
		t->ch = ft_get_input();
		if (ft_isprint(t->ch) || t->ch == ENTER)
			ft_insertion(t);
		if (t->ch == ENTER)
		{
			if (!t->slash && !(t->q_qty % 2))
			{
				ft_end_cycle(t);
				ft_restart_cycle(t);
				continue;
			}
			t->slash = 0;
		}
		else if (t->ch == CTRL_D)
		{
			if (!t->bytes)
				break ;
			if (t->index < t->bytes)
				ft_delete(t);
		}
		else if (t->ch == CTRL_C)
			ft_restart_cycle(t);
		else if (t->ch == BACKSPACE && t->index)
			ft_backspace(t);
		else if (t->ch == 11)
		{
			while (t->start_row > -1)
			{
				ft_setcursor(t->c_col, t->c_row + t->start_row);
				ft_run_capability("dl");
				t->start_row--;
			}
			write(1, PROMPT, (size_t)t->prompt_len);
		}
		if (t->ch == ESCAPE)
			ft_esc_parse(t);
		if (t->ch == -1)
			ft_putstr_fd("error, ft_get_input()\n", STDERR_FILENO);
	}
}
