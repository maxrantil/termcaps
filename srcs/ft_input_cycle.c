/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input_cycle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:46:24 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/11 11:59:21 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

static void	ft_end_cycle(t_term *t)
{
	// ft_setcursor(0, t->total_row + t->start_row + 1);
	/* ft_putchar('\n'); */
	vec_push(&t->v_history, t->inp);
	if (!ft_strcmp(t->inp, "history"))
		ft_history(t);
	ft_memdel((void **)&t->nl_addr);
	if (t->input_cpy)
		ft_strdel(&t->input_cpy);
}

static void ft_restart_cycle(t_term *t)
{
	ft_putendl_fd(t->inp, STDOUT_FILENO);
	ft_memset(t->inp, '\0', BUFFSIZE);
	t->quote = 0;
	t->q_qty = 0;
	t->bytes = 0;
	t->index = 0;
	t->c_col = t->prompt_len;
	t->start_row = ft_get_linenbr();
	t->total_row = 0;
	t->c_row = t->total_row;
	ft_add_nl_last_row(t, 0);
	write(1, PROMPT, t->prompt_len);
	ft_setcursor(t->c_col, t->c_row + t->start_row);
}

void	ft_input_cycle(t_term *t)
{
	ft_add_nl_last_row(t, 0);
	write(1, PROMPT, t->prompt_len);
	while (t->ch != -1)
	{
		t->ch = ft_get_input();
		if (ft_isprint(t->ch) || t->ch == ENTER)
			ft_insertion(t);
		if (t->ch == ENTER)
		{
			if (t->inp[t->bytes - 2] != '\\' && !(t->q_qty % 2))
			{
				ft_end_cycle(t);
				ft_restart_cycle(t);
				continue;
			}
		}
		else if (t->ch == CTRL_D)
		{
			if (t->index < t->bytes)
				ft_delete(t);
			if (!t->bytes)
				break ;
		}
		else if (t->ch == CTRL_C)
			ft_restart_cycle(t);
		else if (t->ch == BACKSPACE && t->index)
			ft_backspace(t);
		if (t->ch == ESCAPE)
			ft_esc_parse(t);
		if (t->inp[t->index])
			ft_print_trail(t);
		if (t->ch == -1)
			ft_putstr_fd("error, ft_get_input()\n", STDERR_FILENO);
	}
}
