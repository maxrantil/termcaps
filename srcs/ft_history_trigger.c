/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history_trigger.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 10:59:10 by mbarutel          #+#    #+#             */
/*   Updated: 2022/12/07 15:40:43 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"


static void	ft_print_new_inp(t_term *t)
{
	int		len;

	while (t->nl_addr[t->c_row])
	{
		if (t->nl_addr[t->c_row + 1])
			len = (int)(t->nl_addr[t->c_row + 1] - t->nl_addr[t->c_row]);
		else
			len = (int)(t->inp + t->bytes - t->nl_addr[t->c_row]);
		if (ft_is_prompt_line(t, t->c_row))
		{
			if (!t->c_row)
				t->c_col = write(STDOUT_FILENO, PROMPT, t->prompt_len);
			else
				t->c_col = write(STDOUT_FILENO, MINI_PROMPT, t->m_prompt_len);
		}
		t->c_col += write(STDOUT_FILENO, t->nl_addr[t->c_row], len);
		if (!t->nl_addr[t->c_row + 1])
			break ;
		t->c_row++;	
	}
}

//TODO: Add back slash handling
static void	ft_reset_nl_addr_prototype(t_term *t, char *inp)
{
	ssize_t	i;
	ssize_t	row;

	i = -1;
	row = t->c_row;
	while (inp[++i])
	{
		t->c_col++;
		if (inp[i] == '\n')
		{
			row++;
			t->c_col = 0;
			t->total_row++;
			ft_add_nl_last_row(t, inp, i+1);
		}
		if (inp[i] == D_QUO || inp[i] == S_QUO)
			ft_quote_handling(t, inp[i]);
	}
	t->bytes = &inp[i] - t->nl_addr[0];
	t->index = t->bytes;
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

void	ft_history_trigger(t_term *t, ssize_t his)
{
	char	*history;
	// ssize_t	total_row;

	if (t->c_row == t->total_row)
	{
		// total_row = t->total_row;
		ft_run_capability("vi");	
		history = (char *)vec_get(&t->v_history, t->v_history.len - (size_t)his);
		if (history)
		{
			t->input_cpy = ft_strdup(t->nl_addr[t->c_row]);
			ft_memset((void *)t->nl_addr[t->c_row], '\0', ft_strlen(t->nl_addr[t->c_row]));
			ft_history_cpy(t->nl_addr[t->c_row], history);
		}
		else
		{
			ft_memset((void *)t->nl_addr[t->c_row], '\0', ft_strlen(t->nl_addr[t->c_row]));
			ft_history_cpy(t->nl_addr[t->c_row], t->input_cpy);
			ft_strdel(&t->input_cpy);
		}
		ft_reset_nl_addr_prototype(t, t->nl_addr[t->c_row]);
		// if (total_row != t->total_row)
			// ft_setcursor(0, ft_get_linenbr() - (t->total_row - total_row));
		ft_setcursor(0, ft_get_linenbr());
		ft_run_capability("cd");
		ft_print_new_inp(t);
		ft_run_capability("ve");
	}
}
