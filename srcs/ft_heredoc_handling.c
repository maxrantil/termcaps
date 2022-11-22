/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_handling.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 12:57:40 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/22 15:00:51 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

void	ft_heredoc_handling(t_term *t)
{
	if (t->index > 2 && t->ch == '<' && !(t->q_qty % 2))
	{
		if (t->inp[t->index - 1] == '<' && t->inp[t->index - 2] != '<')
		{
			t->heredoc = 1;

		}
		else
			t->heredoc = 0;
	}
	/* else
	{
		ssize_t	i;

		i = t->index;
		if (t->ch == '<')
		{
			while (i && t->inp[i] == '<')
				i--;
			if ((t->index - i) == 1)
				t->heredoc = 1;
			else
				t->heredoc = 0;
		}
	} */
}
