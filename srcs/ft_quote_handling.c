/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qoute_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 14:23:10 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/27 14:26:10 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

void	quote_increment(t_term *term)
{
	if (!term->q_qty || (term->q_qty % 2 && !term->quote))
	{
		term->quote = term->ch;
		term->q_qty++;
	}
	else if (!(term->q_qty % 2) && !term->quote)
	{
		term->quote = term->ch;
		term->q_qty++;
	}
	else if (term->ch == term->quote)
	{
		term->quote = 0;
		term->q_qty++;
	}
}

void quote_decrement(char *input, t_term *term)
{
	if (!(term->q_qty % 2))
	{	
		term->quote = input[term->indx - 1];
		term->q_qty--;
	}
	else if ((term->q_qty % 2) && term->quote == input[term->indx - 1])
	{
		term->quote = 0;
		term->q_qty--;
	}
}