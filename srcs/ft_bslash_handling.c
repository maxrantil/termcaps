/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bslash_handling.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 16:28:08 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/21 18:33:35 by mbarutel         ###   ########.fr       */
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
