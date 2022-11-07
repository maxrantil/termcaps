/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_prompt_len.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:59:55 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/07 15:18:19 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/**
 * It returns the length of the prompt on the given row
 * 
 * @param term the term structure
 * @param row the row of the cursor
 * 
 * @return The length of the prompt.
 */
size_t	ft_get_prompt_len(t_term *term, size_t row)
{
	size_t	prompt_len;

	prompt_len = 0;
	if (!row)
		prompt_len = term->prompt_len;
	else if (ft_is_prompt_line(term, row))
		prompt_len = term->m_prompt_len;
	return (prompt_len);
}
