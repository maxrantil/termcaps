/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_prompt_len.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:59:55 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/09 10:17:09 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

size_t	ft_get_prompt_len(t_term *t, size_t row)
{
	size_t	prompt_len;

	prompt_len = 0;
	if (!row)
		prompt_len = t->prompt_len;
	else if (ft_is_prompt_line(t, row))
		prompt_len = t->m_prompt_len;
	return (prompt_len);
}
