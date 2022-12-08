/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nl_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 15:00:30 by mbarutel          #+#    #+#             */
/*   Updated: 2022/12/08 15:57:34 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

void	ft_nl_removal(t_term *t) // bug here
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (t->history_buff[i])
	{
		if (i && t->history_buff[i] == '\n' && (t->history_buff[i - 1] == '\\' || !t->history_buff[i + 1]))
			i++;
		t->history_buff[j++] = t->history_buff[i++];	
	}
}
