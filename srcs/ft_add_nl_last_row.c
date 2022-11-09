/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_nl_last_row.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 13:42:45 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/09 09:42:34 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

void	ft_add_nl_last_row(t_term *term, size_t pos)
{
	int		index;
	char	**fresh_array;

	index = -1;
	fresh_array = NULL;
	if (!term->nl_addr)
	{
		term->nl_addr = (char **)ft_memalloc(sizeof(char *) * 2);
		term->nl_addr[++index] = &term->inp[pos];
		term->nl_addr[++index] = NULL;
	}
	else
	{
		fresh_array = (char **)ft_memalloc(sizeof(char *) \
		* (term->total_row + 2));
		while (term->nl_addr[++index])
			fresh_array[index] = term->nl_addr[index];
		fresh_array[index++] = &term->inp[pos];
		fresh_array[index] = NULL;
		ft_memdel((void **)&term->nl_addr);
		term->nl_addr = fresh_array;
	}
}
