/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote_decrement.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 14:23:10 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/08 13:54:42 by mrantil          ###   ########.fr       */
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
void	ft_quote_decrement(char *input, t_term *term, int num)
{
	if (!(term->q_qty % 2))
	{	
		term->quote = input[term->index - num];
		term->q_qty--;
	}
	else if ((term->q_qty % 2) && term->quote == input[term->index - num])
	{
		term->quote = 0;
		term->q_qty--;
	}
}
