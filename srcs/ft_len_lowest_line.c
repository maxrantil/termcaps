/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_len_lowest_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:17:14 by mrantil           #+#    #+#             */
/*   Updated: 2022/12/14 17:32:33 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/*
 * It returns the length of the line at the given row
 *
 * @param t the term structure
 * @param row the row of the cursor
 *
 * @return The length of the lowest line.
 */
ssize_t	ft_len_lowest_line(t_term *t, ssize_t row)
{
	ssize_t	len;

	if (t->nl_addr[row + 1])
	{
		if (!row)
			len = t->nl_addr[row + 1] - t->nl_addr[row];
		else
			len = t->nl_addr[row + 1] - t->nl_addr[row] - 1;
	}
	else
		len = &t->inp[t->bytes] - t->nl_addr[row];
	len += ft_get_prompt_len(t, row);
	return (len);
}
