/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote_decrement.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 14:23:10 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/09 09:59:39 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

void	ft_quote_decrement(t_term *term, int num)
{
	if (!(term->q_qty % 2))
	{	
		term->quote = term->inp[term->index - num];
		term->q_qty--;
	}
	else if ((term->q_qty % 2) && term->quote == term->inp[term->index - num])
	{
		term->quote = 0;
		term->q_qty--;
	}
}
