/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history_trigger.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 10:59:10 by mbarutel          #+#    #+#             */
/*   Updated: 2022/12/06 21:53:50 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

// /*
//  * It moves the cursor to the end of the line
//  *
//  * @param t the term structure
//  */
// static void	ft_history_trigger_end(t_term *t, int display_row)
// {
// 	t->index = t->bytes;
// 	t->c_row = t->total_row;
// 	if (ft_is_prompt_line(t, t->c_row))
// 	{
// 		if (!t->c_row)
// 			t->c_col = t->prompt_len;
// 		else
// 			t->c_col = t->m_prompt_len;
// 	}
// 	t->c_col += &t->inp[t->bytes] - t->nl_addr[t->c_row];
// 	ft_setcursor(t->c_col, display_row + t->total_row);
// 	ft_run_capability("ve");
// }

// /*
//  * It sets the cursor to the beginning of the line, clears the screen, and
//  * prints the prompt
//  *
//  * @param t the term structure
//  */
// static void	ft_history_trigger_start(t_term *t, int display_row)
// {
// 	ft_run_capability("vi");
// 	t->quote = 0;
// 	t->q_qty = 0;
// 	t->c_col = 0;
// 	ft_setcursor(t->c_col, display_row);
// 	t->c_row = 0;
// 	t->index = 0;
// 	t->total_row = 0;
// 	ft_run_capability("cd");
// 	ft_putstr(PROMPT);
// }

// /*
//  * It takes a history number,
//  * and if it exists, it copies it into the input buffer, otherwise it copies the
//  * original input buffer
//  *
//  * @param t the term structure
//  * @param his the history number to trigger
//  */
// void	ft_history_trigger(t_term *t, ssize_t his)
// {
// 	char	*history;
// 	int 	display_row;

// 	if (t->start_row == t->ws_row)
// 		display_row = t->start_row - t->c_row;
// 	else
// 		display_row = t->start_row;
// 	ft_history_trigger_start(t, display_row);
// 	history = (char *)vec_get(&t->v_history, t->v_history.len - (size_t)his);
// 	if (history)
// 	{
// 		t->bytes = (ssize_t)ft_strlen(history);
// 		if (!t->input_cpy)
// 			t->input_cpy = ft_strdup(t->inp);
// 		ft_memset((void *)t->inp, '\0', BUFF_SIZE);
// 		ft_memcpy((void *)t->inp, (void *)history, (size_t)t->bytes);
// 		// ft_memset((void *)t->nl_addr[t->c_row], '\0', BUFF_SIZE);
// 		// ft_memcpy((void *)t->nl_addr[t->c_row], (void *)history, (size_t)t->bytes);
// 	}
// 	else
// 	{
// 		t->bytes = (ssize_t)ft_strlen(t->input_cpy);
// 		// ft_memset((void *)t->nl_addr[t->c_row], '\0', BUFF_SIZE);
// 		// ft_memcpy((void *)t->nl_addr[t->c_row], (void *)history, (size_t)t->bytes);	
// 		ft_memset((void *)t->inp, '\0', BUFF_SIZE);
// 		ft_memcpy((void *)t->inp, (void *)t->input_cpy, (size_t)t->bytes);
// 		ft_strdel(&t->input_cpy);
// 	}
// 	ft_reset_nl_addr(t);
// 	ft_print_trail(t);
// 	ft_history_trigger_end(t, display_row);
// }
/*
 * It moves the cursor to the end of the line
 *
 * @param t the term structure
 */
// static void	ft_history_trigger_end(t_term *t)
// {
// 	t->index = t->index;;
// 	ft_run_capability("ve");
// }

static void	ft_history_trigger_start(t_term *t)
{
	ft_run_capability("vi");
	ft_setcursor(0, ft_get_linenbr());
	ft_run_capability("cd");
	if (!t->c_row)
		ft_putstr(PROMPT);
}

static void	ft_print_new_inp(t_term *t)
{
	int		i;
	int		len;

	i = t->c_row - 1;
	while (t->nl_addr[++i])
	{
		if (t->nl_addr[i + 1])
			len = (int)(t->nl_addr[i + 1] - t->nl_addr[i]);
		else
			len = (int)(t->inp + t->bytes - t->nl_addr[i]);
		if (i && t->nl_addr[i] && ft_is_prompt_line(t, i))
			ft_putstr(MINI_PROMPT);
		write(1, t->nl_addr[i], len);
	}
	t->c_row = i - 1;
}

static void	ft_reset_nl_addr_prototype(t_term *t, char *inp)
{
	ssize_t	i;
	ssize_t	len;
	ssize_t	row;

	i = 0;
	len = 0;
	row = t->c_row;
	// ft_putchar('[');
	// ft_putchar(inp[i]);
	// ft_putchar(']');
	while (inp[i])
	{
		len++;
		t->c_col = len;
		if (((len + ft_get_prompt_len(t, row)) + 1) == t->ws_col || inp[i] == '\n')
		{
			ft_add_nl_last_row(t, i + 1);
			row++;
			t->total_row++;
			len = -1;
		}
		if (inp[i] == D_QUO || inp[i] == S_QUO)
			ft_quote_handling(t, inp[i]);
		i++;
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

	if (t->c_row == t->total_row)
	{
		ft_history_trigger_start(t);
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
		ft_print_new_inp(t);
		// ft_history_trigger_end(t);
		ft_run_capability("ve");
	}
}
