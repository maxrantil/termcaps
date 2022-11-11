/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_row_lowest_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 15:21:37 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/09 10:21:32 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

size_t	ft_row_lowest_line(t_term *t)
{
	size_t	row;

	row = t->c_row;
	while (t->nl_addr[row + 1] && !ft_is_prompt_line(t, row + 1))
		row++;
	return (row);
}
