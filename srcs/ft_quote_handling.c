/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote_handling.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 14:23:10 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/08 14:43:04 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/**
 * If the quote character is not set, set it. If it is set, unset it
 * 
 * @param term the term structure
 * @param ch the character that was just typed
 */
void	ft_quote_handling(t_term *term, char ch)
{
	if (!term->q_qty || (term->q_qty % 2 && !term->quote))
	{
		term->quote = ch;
		term->q_qty++;
	}
	else if (!(term->q_qty % 2) && !term->quote)
	{
		term->quote = ch;
		term->q_qty++;
	}
	else if (ch == term->quote)
	{
		term->quote = 0;
		term->q_qty++;
	}
}
