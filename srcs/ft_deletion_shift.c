/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deletion_shift.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 15:21:37 by mbarutel          #+#    #+#             */
/*   Updated: 2022/12/08 22:32:15 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/*
 * It deletes a character from the input string and shifts the rest of the
 * string to the left
 *
 * @param t the t_term struct
 * @param mode 0 for backspace, 1 for delete
 */
void	ft_deletion_shift(t_term *t, int index)
{
	t->inp[index] = '\0';
	while (&t->inp[index] < &t->inp[t->bytes])
	{
		t->inp[index] = t->inp[index] ^ t->inp[index + 1];
		t->inp[index + 1] = t->inp[index] ^ t->inp[index + 1];
		t->inp[index] = t->inp[index] ^ t->inp[index + 1];
		index++;
	}
	t->bytes--;
}
// void	ft_deletion_shift(, int index)
// {
// 	inp[index] = '\0'; // This way of dereferencing the pointer might not allowed in 42
// 	ft_printf("%d", index
// 	while (inp[index] < inp[(*bytes)])
// 	{
// 		// ft_putendl("This happens");
// 		inp[index] = inp[index] ^ inp[index + 1];
// 		inp[index + 1] = inp[index] ^ inp[index + 1];
// 		inp[index] = inp[index] ^ inp[index + 1];
// 		index++;
// 	}
// 	(*bytes)--;
// }
