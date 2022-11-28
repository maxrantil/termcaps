/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bslash_handling.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 16:28:08 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/28 12:10:49 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

void	ft_bslash_handling(t_term *t)
{
	ssize_t	i;

	i = t->index - 1;
	if (t->ch == '\\' && t->index == t->bytes && !t->heredoc)
	{
		while (i && t->inp[i] == '\\')
			i--;
		if ((t->index - i) % 2)
			t->bslash = 1;
		else
			t->bslash = 0;
	}
	else
		if (t->ch != D_QUO && t->ch != S_QUO)
			t->bslash = 0;
}
