/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deletion_shift.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 15:21:37 by mbarutel          #+#    #+#             */
/*   Updated: 2022/12/14 11:51:24 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/*
 * It deletes a character from the input string and shifts the rest of the
 * string to the left
 *
 * @param t the t_term struct
 * @param mode 0 for backspace, 1 for delete
 */
void	ft_deletion_shift(t_term *t, ssize_t index)
{
	int blash;
	int	heredoc;

	blash = 0;
	heredoc = 0;
	if (t->inp[index] == '<')
		heredoc = 1;
	else if (t->inp[index] == '\\')
		blash = 1;
	else if ((t->inp[index] == D_QUO || t->inp[index] == S_QUO) \
		&& !ft_bslash_escape_check(t, index))
		ft_quote_decrement(t, index);
	t->inp[index] = '\0';
	while (&t->inp[index] < &t->inp[t->bytes])
	{
		t->inp[index] = t->inp[index] ^ t->inp[index + 1];
		t->inp[index + 1] = t->inp[index] ^ t->inp[index + 1];
		t->inp[index] = t->inp[index] ^ t->inp[index + 1];
		index++;
	}
	t->bytes--;
	if (blash)
		ft_quote_flag_check(t, t->index);
	else if (heredoc) // if t->delim exits, delete
	{
		ft_heredoc_handling(t, t->index - 1);
		if (!t->heredoc && t->delim)
			ft_strdel(&t->delim);
	}
}
