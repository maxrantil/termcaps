/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote_decrement.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 14:23:10 by mbarutel          #+#    #+#             */
/*   Updated: 2022/12/13 16:25:26 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/*
 * If the quote quantity is even, then the quote is set to the character at
 * the index minus the number of characters to move back. If the quote quantity
 * is odd and the quote is equal to the character at the index minus the number
 * of characters to move back, then the quote is set to zero
 *
 * @param t the term structure
 * @param num the number of characters to be deleted
 */
void	ft_quote_decrement(t_term *t, ssize_t index)
{
	if (!(t->q_qty % 2))
	{
		t->quote = t->inp[index];
		t->q_qty--;
	}
	else if ((t->q_qty % 2) && t->quote == t->inp[index])
	{
		t->quote = 0;
		t->q_qty--;
	}
}
// void	ft_quote_decrement(t_term *t, int num)
// {
// 	int blash_loc;

// 	blash_loc = t->index - (num - 1);
// 	if (!(t->q_qty % 2) && (t->index < 2 || t->inp[blash_loc] != '\\'))
// 	{
// 		t->quote = t->inp[t->index - num];
// 		t->q_qty--;
// 	}
// 	else if (((t->q_qty % 2) && t->quote == t->inp[t->index - num]) && (t->index < 2 || t->inp[blash_loc] != '\\'))
// 	{
// 		t->quote = 0;
// 		t->q_qty--;
// 	}
// }
