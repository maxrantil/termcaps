/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_nl_addr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:13:40 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/09 10:13:59 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/**
 * It removes a row from the
 * `nl_addr` array
 * 
 * @param term the term structure
 * @param row the row number of the line to be removed
 */
void	ft_remove_nl_addr(t_term *t, size_t row)
{
	size_t	i;
	size_t	j;
	char	**new_array;

	i = -1;
	j = -1;
	new_array = (char **)ft_memalloc(sizeof(char *) * t->total_row + 1);
	while (t->nl_addr[++i])
	{
		if (i != row)
			new_array[++j] = t->nl_addr[i];
	}
	new_array[++j] = NULL;
	ft_memdel((void **)&t->nl_addr);
	t->nl_addr = new_array;
}
