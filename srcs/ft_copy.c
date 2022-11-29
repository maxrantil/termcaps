/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 13:02:11 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/29 16:37:51 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/*
 * It copies the word before the cursor to the clipboard
 *
 * @param t The term structure
 */
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
