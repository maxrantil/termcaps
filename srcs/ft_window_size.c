/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_window_size.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 17:25:07 by mrantil           #+#    #+#             */
/*   Updated: 2022/12/08 23:18:15 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

// static void	ft_print_new_inp_proto(t_term *t)
// {
// 	int		len;

// 	while (t->nl_addr[t->c_row])
// 	{
// 		// if (t->nl_addr[t->c_row + 1])
// 		// {

// 		// 	if (&t->inp[t->index] > t->nl_addr[t->c_row] && &t->inp[t->index] < t->nl_addr[t->c_row + 1])
// 		// 		t->c_col += &t->inp[t->index] - t->nl_addr[t->c_row] + ft_get_prompt_len(t, t->c_row);
// 		// }
// 		// else
// 		// 	if (&t->inp[t->index] > t->nl_addr[t->c_row] && &t->inp[t->index] < &t->inp[t->bytes])
// 		// 		t->c_col += &t->inp[t->index] - t->nl_addr[t->c_row] + ft_get_prompt_len(t, t->c_row);
// 		if (t->nl_addr[t->c_row + 1])
// 			len = (int)(t->nl_addr[t->c_row + 1] - t->nl_addr[t->c_row]);
// 		else
// 			len = (int)(t->inp + t->bytes - t->nl_addr[t->c_row]);
// 		if (ft_is_prompt_line(t, t->c_row))
// 		{
// 			if (!t->c_row)
// 				t->c_col = write(STDOUT_FILENO, PROMPT, t->prompt_len);
// 			else
// 				t->c_col = write(STDOUT_FILENO, MINI_PROMPT, t->m_prompt_len);
// 		}
// 		else
// 			t->
// 		t->c_col += write(STDOUT_FILENO, t->nl_addr[t->c_row], len);
// 		if (!t->nl_addr[t->c_row + 1])
// 			break ;
// 		t->c_row++;	
// 	}
// }

static ssize_t get_new_row(t_term *t)
{
	char	*end;
	ssize_t	row;

	row = -1;
	while (t->nl_addr[++row])
	{
		if (t->nl_addr[row + 1])
			end = t->nl_addr[row + 1];
		else
			end = &t->inp[t->bytes];
		if (&t->inp[t->index] >= t->nl_addr[row] && &t->inp[t->index] <= end)
			return (row);
		row++;
	}
	return (0);
}

void	ft_reset_nl_addr_proto(t_term *t)
{
	ssize_t	i;
	ssize_t	len;

	i = -1;
	len = 0;
	t->total_row = 0;
	if (t->nl_addr)
		ft_memdel((void **)&t->nl_addr);
	ft_add_nl_last_row(t, t->inp, 0);
	while (t->inp[++i])
	{
		len++;
		if (((len + ft_get_prompt_len(t, t->total_row))) == t->ws_col \
			|| t->inp[i] == '\n')
		{
			ft_add_nl_last_row(t, t->inp, i + 1);
			t->total_row++;
			len = 0;
		}
		if (t->inp[i] == D_QUO || t->inp[i] == S_QUO)
			ft_quote_handling(t, t->inp[i]);
	}
}

/*
 * It resets the cursor position and prints the trail of the input string
 *
 * @param t the term structure
 */
void	ft_window_size(t_term *t)
{
	struct winsize	size;

	ft_run_capability("vi");
	if (ioctl(0, TIOCGWINSZ, (char *)&size) < 0)
		perror("TIOCGWINSZ");
	t->ws_col = size.ws_col;
	t->ws_row = size.ws_row;
	if (*t->inp) // here, set the cursor positoin
	{
		ft_run_capability("sc");
		ft_run_capability("cl");
		t->quote = 0;
		t->q_qty = 0;
		t->bslash = 0;
		t->heredoc = 0;
		ft_reset_nl_addr(t);
		// set_new_cur_pos(t);
		ft_print_input(t, 0, 0); // t->c_row should not be changed here
		ft_run_capability("rc");
		t->c_row = get_new_row(t);
		t->c_col = &t->inp[t->index] - t->nl_addr[t->c_row];
	}
	ft_run_capability("ve");
}
