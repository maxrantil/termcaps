/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shift_insert.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 13:11:43 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/28 12:24:54 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

void	ft_shift_insert(t_term *t)
{
	ssize_t	bytes_cpy;

	bytes_cpy = t->bytes;
	while (&t->inp[bytes_cpy] >= &t->inp[t->index])
	{
		t->inp[bytes_cpy] = t->inp[bytes_cpy] ^ t->inp[bytes_cpy + 1];
		t->inp[bytes_cpy + 1] = t->inp[bytes_cpy] ^ t->inp[bytes_cpy + 1];
		t->inp[bytes_cpy] = t->inp[bytes_cpy] ^ t->inp[bytes_cpy + 1];
		bytes_cpy--;
	}
}
