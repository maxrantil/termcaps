/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_prompt_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 14:26:34 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/08 16:56:38 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/**
 * It returns the address of the first character of a line if the line is a
 * prompt line, otherwise it
 * returns NULL
 * 
 * @param term the term structure
 * @param row the row of the cursor
 * 
 * @return The address of the first character of the line.
 */
char	*ft_is_prompt_line(t_term *term, size_t row)
{
	if (!row || term->nl_addr[row][-1] == '\n')
		return (term->nl_addr[row]);
	return (NULL);
}
