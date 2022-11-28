/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote_handling.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 14:23:10 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/28 10:01:08 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/**
 * If the quote character is not set, set it. If it is set, unset it
 * 
 * @param term the term structure
 * @param ch the character that was just typed
 */
void	ft_quote_handling(t_term *t, char ch)
{
	if (!t->q_qty || (t->q_qty % 2 && !t->quote))
	{
		t->quote = ch;
		t->q_qty++;
	}
	else if (!(t->q_qty % 2) && !t->quote)
	{
		t->quote = ch;
		t->q_qty++;
	}
	else if (ch == t->quote)
	{
		t->quote = 0;
		t->q_qty++;
	}
}
