/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alt_move.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:49:38 by mrantil           #+#    #+#             */
/*   Updated: 2022/10/11 12:18:26 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"

void	alt_move(char *input)
{
	char		*ptr;
	static int	word;
	int			x;
	int			b;
	
	b = 0;
	ptr = input;
	x = ft_strlen(input) - word;
	while (x >= 0 && ptr[x] != ' ')
	{
		x--;
		b++;
	}
	while (x >= 0 && ptr[x] == ' ')
	{
		x--;
		b++;
	}
	word = ft_strlen(input) - x;
	char *y = ft_itoa(b);
	write(1, "\033[", 2);
	write(1, y, ft_strlen(y));
	write(1, "D", 1);
}
