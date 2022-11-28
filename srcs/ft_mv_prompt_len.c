/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mv_prompt_len.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:23:57 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/28 12:37:23 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

ssize_t	ft_mv_prompt_len(t_term *t, int num)
{
	ssize_t	prompt_len;

	prompt_len = 0;
	if (t->c_row == 1 && (num < 0))
		prompt_len = t->prompt_len;
	else if (ft_is_prompt_line(t, t->c_row + num))
		prompt_len = t->m_prompt_len;
	return (prompt_len);
}
