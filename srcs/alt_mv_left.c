/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alt_mv_left.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:49:38 by mrantil           #+#    #+#             */
/*   Updated: 2022/10/11 16:45:56 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"

void	alt_mv_left(int *cursor, char *input)
{
	int	b;

	b = 0;
	while (cursor[0] > 0 && ft_isspace(&input[cursor[0]]))
	{
		b++;
		cursor[0]--;
	}
	while (cursor[0] > 0 && !ft_isspace(&input[cursor[0]]))
	{
		b++;
		cursor[0]--;
	}
	if (b)
	{
		write(1, "\033[", 2);
		write(1, ft_itoa(b), ft_intlen(b));
		write(1, "D", 1);
	}
}
