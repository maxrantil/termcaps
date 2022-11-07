/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote_decrement.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 14:23:10 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/07 16:18:58 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/**
 * If the quote quantity is even, set the quote to the character before 
 * the current index, and decrement the quote quantity. If the quote quantity 
 * is odd, and the quote is the character before
 * the current index, set the quote to 0 and decrement the quote quantity
 * 
 * @param input the input string
 * @param term the t_term structure
 */
void	ft_quote_decrement(char *input, t_term *term)
{
	if (!(term->q_qty % 2))
	{	
		term->quote = input[term->index - 1];
		term->q_qty--;
	}
	else if ((term->q_qty % 2) && term->quote == input[term->index - 1])
	{
		term->quote = 0;
		term->q_qty--;
	}
}
