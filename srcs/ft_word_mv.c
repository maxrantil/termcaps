/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_word_mv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:43:30 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/11 15:28:40 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

static void	ft_word_left(t_term *t)
{
	while (t->index && ft_isspace(&t->inp[t->index - 1]))
	{
		if (&t->inp[t->index + 1] == t->nl_addr[t->c_row])
			break ;
		t->index--;
	}
	while (t->index && !ft_isspace(&t->inp[t->index - 1]))
	{
		if (&t->inp[t->index] == t->nl_addr[t->c_row])
			break ;
		t->index--;
	}
	t->c_col = &t->inp[t->index] - t->nl_addr[t->c_row];
	if (t->nl_addr[t->c_row] == &t->inp[0])
		t->c_col += t->prompt_len;
	else if (ft_is_prompt_line(t, t->c_row))
		t->c_col += t->m_prompt_len;
	ft_setcursor(t->c_col, ft_get_linenbr());
}

// static void	ft_word_right(t_term *t)
// {
// 	ssize_t	row;

// 	row = t->c_row + 1;
// 	while (t->index < t->bytes && ft_isspace(&t->inp[t->index]))
// 	{
// 		if (t->nl_addr[row] \
// 		&& &t->inp[t->index + 1] == t->nl_addr[row])
// 			break ;
// 		t->index++;
// 	}
// 	while (t->index < t->bytes && !ft_isspace(&t->inp[t->index]))
// 	{
// 		if (t->nl_addr[row] \
// 		&& &t->inp[t->index + 1] == t->nl_addr[row])
// 			break ;
// 		t->index++;
// 	}
// 	t->c_col = &t->inp[t->index] - t->nl_addr[row - 1];
// 	if (t->nl_addr[row - 1] == &t->inp[0])
// 		t->c_col += t->prompt_len;
// 	else if (ft_is_prompt_line(t, row - 1))
// 		t->c_col += t->m_prompt_len;
// 	ft_setcursor(t->c_col, row + t->start_row);
// }
static void	ft_word_right(t_term *t)
{
	ssize_t	row;

	row = t->c_row;
	while (t->index < t->bytes && ft_isspace(&t->inp[t->index]))
	{
		if (t->nl_addr[row + 1] && &t->inp[t->index + 1] == t->nl_addr[row + 1])
			break ;
		t->index++;
	}
	while (t->index < t->bytes && !ft_isspace(&t->inp[t->index]))
	{
		if (t->nl_addr[row + 1] \
		&& &t->inp[t->index + 1] == t->nl_addr[row + 1])
			break ;
		t->index++;
	}
	t->c_col = &t->inp[t->index] - t->nl_addr[row];
	if (t->nl_addr[row] == &t->inp[0])
		t->c_col += t->prompt_len;
	else if (ft_is_prompt_line(t, row))
		t->c_col += t->m_prompt_len;
	// ft_setcursor(t->c_col, ft_display_row_v2(t, row));
	ft_setcursor(t->c_col, ft_get_linenbr());
}

void	ft_word_mv(t_term *t)
{
	if (t->ch == 98 && (&t->inp[t->index] > t->nl_addr[t->c_row]))
		ft_word_left(t);
	else if (t->ch == 102 && (t->index < t->bytes))
	{
		// if (t->nl_addr[t->c_row + 1])
		// {
		// 	if (&t->inp[t->index] < &t->nl_addr[t->c_row + 1][-1])
		// 		ft_word_right(t);
		// }
		// else
		ft_word_right(t);
	}
}
