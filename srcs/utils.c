/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 07:52:49 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/13 15:12:58 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"

int	get_input(void)
{
	int	c;

	c = 0;
	read(STDIN_FILENO, &c, 1);
	// printf("c[%d] ", c);
	return (c);
}

void	print_trail(char *input, int cursor)
{
	ft_putstr("\033[s");
	ft_putstr(&input[cursor]);
	ft_putstr("\033[H");
	ft_putstr("\033[u");
}

void	clear_trail(void)
{
	ft_putstr("\033[K");
}
