/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nl_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 15:00:30 by mbarutel          #+#    #+#             */
/*   Updated: 2022/12/06 21:27:27 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

void	ft_nl_removal(t_term *t)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (t->inp[i])
	{
		if (i && t->inp[i] == '\n' && t->inp[i - 1] == '\\')
			i++;
		t->history_buff[j++] = t->inp[i++];	
	}
}
