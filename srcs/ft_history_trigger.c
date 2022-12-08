/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history_trigger.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 10:59:10 by mbarutel          #+#    #+#             */
/*   Updated: 2022/12/08 23:01:58 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

static ssize_t	ft_reset_nl_addr_prototype(t_term *t, char *inp)
{
	ssize_t	i;
	ssize_t	col;
	ssize_t	row;

	i = -1;
	row = t->c_row;
	while (inp[++i])
	{
		col++;
		if (((col + ft_get_prompt_len(t, row))) == t->ws_col || inp[i] == '\n') 
		{
			row++;
			col = 0;
			t->total_row++;
			ft_add_nl_last_row(t, inp, i+1);
		}
	}
	t->bytes = &inp[i] - t->nl_addr[0];
	t->index = t->bytes;
	return (row);
}

static void	ft_history_cpy(char *dst, char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (src[i])
	{
		if (src[i] == '\\' && (src[i + 1] && src[i + 1] != '\'' && src[i + 1] != '"'))
			i++;
		dst[j++] = src[i++];
	}
}

static void ft_push_history(t_term *t)
{
	ft_nl_removal(t);
	vec_push(&t->v_history, t->history_buff);
}

static void ft_flag_reset(t_term *t)
{
	int	i;

	i = -1;
	t->q_qty = 0;
	t->quote = 0;
	t->bslash = 0;
	t->heredoc = 0;
	while (t->inp[++i])
	{
		ft_heredoc_handling(t, t->inp[i], i);
		if ((t->inp[i] == D_QUO || t->inp[i] == S_QUO) && !t->heredoc)
		{
			if (!t->bslash)
				ft_quote_handling(t, t->inp[i]);
			else
				t->bslash = 0;
		}
	}
}

void	ft_history_trigger(t_term *t, ssize_t his)
{
	char	*history;
	ssize_t	row;

	if (t->c_row == t->total_row)
	{
		row = t->c_row;
		if (t->history_row == -1) // something to to with this value
		{
			if (t->input_cpy)
				ft_strdel(&t->input_cpy);
			t->input_cpy = ft_strsub(t->nl_addr[t->c_row], 0, ft_strlen(t->nl_addr[t->c_row]));
			if (*t->history_buff)
			{
				ft_push_history(t);
				ft_memset((void *)t->history_buff, '\0', ft_strlen(t->history_buff));
			}
			t->history_row = t->c_row;
		}
		t->c_row = t->history_row;
		ft_run_capability("vi");	
		history = (char *)vec_get(&t->v_history, t->v_history.len - (size_t)his);
		if (history)
		{
			ft_memset((void *)t->nl_addr[t->c_row], '\0', ft_strlen(t->nl_addr[t->c_row]));
			ft_history_cpy(t->nl_addr[t->c_row], history);
		}
		else
		{
			ft_memset((void *)t->nl_addr[t->c_row], '\0', ft_strlen(t->nl_addr[t->c_row]));
			if (t->input_cpy)
				ft_history_cpy(t->nl_addr[t->c_row], t->input_cpy);
		}
		ft_reset_nl_addr_prototype(t, t->nl_addr[t->history_row]);
		if (row > t->history_row)
		{
			ft_setcursor(0, ft_get_linenbr() - (row - t->history_row));
			while (row > t->history_row)
			{
				ft_remove_nl_addr(t, row);
				t->total_row--;
				row--;
			}
		}
		else
			ft_setcursor(0, ft_get_linenbr());
		ft_run_capability("cd");
		ft_flag_reset(t);
		ft_print_input(t, t->c_row, 1);
		// ft_putnbr(t->c_col);
		if (!history)
			t->history_row = -1;
		ft_run_capability("ve");
	}
}
