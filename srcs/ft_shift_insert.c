/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shift_insert.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 13:11:43 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/25 13:12:00 by mbarutel         ###   ########.fr       */
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