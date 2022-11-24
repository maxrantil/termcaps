/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_paste.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 20:36:40 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/24 20:41:36 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

void ft_paste(t_term *t)
{
	int	i;

	i = -1;
	while (t->clipboard[++i])
	{
		ft_putc(t->clipboard[i]);
		ft_shift_nl_addr(t, 1);
		if (t->inp[t->index])
			ft_shift_insert(t);
		t->inp[t->index++] = (char)t->ch;
	}
}