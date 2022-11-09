/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input_cycle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:46:24 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/09 15:25:26 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

static void	ft_end_cycle(t_term *t)
{
	ft_setcursor(0, t->total_row + 1);
	vec_push(&t->v_history, t->inp);
	if (!ft_strcmp(t->inp, "history"))
		ft_history(t);
	ft_memdel((void **)&t->nl_addr);
	if (t->input_cpy)
		ft_strdel(&t->input_cpy);
}

static int	ft_get_linenbr()
{
	char	buf[16];
	int		len;
	int		i;

	ft_memset(buf, '\0', sizeof(buf));
	write(0, "\033[6n", 4);
	len = 0;
	while (read(0, buf + len, 1) == 1)
	{
		if (buf[len++] == 'R')
			break;
	}
	len = 0;
	i = -1;
	while (buf[i++] != ';')
	{
		if (ft_isdigit(buf[i]))
			buf[len++] = buf[i];
	}
	buf[len] = '\0';
	return (ft_atoi(buf));
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
	t->total_row = ft_get_linenbr();
	t->c_row = t->total_row - 1;
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
				ft_add_nl_last_row(t, 0);
				write(1, PROMPT, t->prompt_len);
				ft_setcursor(t->c_col, t->c_row);
				continue;
			}
		}
		else if (t->ch == CTRL_D && t->index < t->bytes)
			ft_delete(t);
		else if (t->ch == CTRL_C)
			break ;
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
