/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alt_mv_right.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:49:38 by mrantil           #+#    #+#             */
/*   Updated: 2022/10/11 16:42:59 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"

void	alt_mv_right(int *cursor, char *input)
{
	int	b;
	int	len;

	len = ft_strlen(input);
	b = 0;
	while (cursor[0] < len && ft_isspace(&input[cursor[0]]))
	{
		b++;
		cursor[0]++;
	}
	while (cursor[0] < len && !ft_isspace(&input[cursor[0]]))
	{
		b++;
		cursor[0]++;
	}
	if (b)
	{
		write(1, "\033[", 2);
		write(1, ft_itoa(b), ft_intlen(b));
		write(1, "C", 1);
	}
}
