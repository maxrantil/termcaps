/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_prompt_len.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:59:55 by mrantil           #+#    #+#             */
/*   Updated: 2022/12/07 15:11:04 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/*
 * It returns the prompt length of the given row
 *
 * @param t the term structure
 * @param row the row of the cursor
 *
 * @return The length of the prompt.
 */
ssize_t	ft_get_prompt_len(t_term *t, ssize_t row)
{
	if (!row)
		return (t->prompt_len);
	if (t->nl_addr[row][-1] == '\n')
		return (t->m_prompt_len);
	return (0);
}
// ssize_t	ft_get_prompt_len(t_term *t, ssize_t col, ssize_t row, ssize_t index)
// {
// 	ssize_t len;

// 	if (!row)
// 		return (t->prompt_len);
// 	len = &t->inp[index] - t->nl_addr[row];
// 	if ((col - len) > 0)
// 		return (t->m_prompt_len);
// 	else
// 		return (0);
// }
// ssize_t	ft_get_prompt_len(t_term *t, ssize_t col, ssize_t row)
// {
// 	ssize_t	prompt_len;

// 	prompt_len = 0;
// 	// ft_printf("c_col %d\n", t->c_col);
// 	// ft_printf("tc_col %d\n", col);
// 	if (!row)
// 		prompt_len = t->prompt_len;
// 	else
// 	{
// 		while (col && ((t->nl_addr[row] + col) >= t->nl_addr[row]))
// 		{
// 			// ft_putchar(t->nl_addr[row][col]);
// 			col--;
// 		}
// 		// ft_printf("c_col %d\n", col);
// 		if (!col)
// 			prompt_len = t->m_prompt_len;
// 	}
// 	// else if (ft_is_prompt_line(t, row))
// 	// 	prompt_len = t->m_prompt_len;
// 	return (prompt_len);
// }
