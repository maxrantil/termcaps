/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 13:02:11 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/25 15:32:05 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

void	ft_copy(t_term *t)
{
	ssize_t	i;
	ssize_t	j;

	i = t->index - 1;
	while (i && ft_isspace(&t->inp[i]))
		i--;
	j = i;
	while (j && !ft_isspace(&t->inp[j]))
		j--;
	if (ft_isspace(&t->inp[j]))
		j++;
	if (t->clipboard.buff)
		ft_strdel(&t->clipboard.buff);
	t->clipboard.buff = ft_strsub(&t->inp[j], 0, (size_t)((i - j) + 1));
	t->clipboard.type = COPY;
}
