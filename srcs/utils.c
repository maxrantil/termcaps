/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 07:52:49 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/20 12:07:59 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

int	get_input(void)
{
	int	c;

	c = 0;
	read(STDIN_FILENO, &c, 1);
	// printf("c[%d]\n", c);		//save this for testing
	return (c);
}

void	print_trail(char *input, t_term *cap)
{
	ft_putstr("\033[s");
	ft_putstr(&input[cap->cursor]);
	ft_putstr("\033[H");
	ft_putstr("\033[u");
}

void	clear_trail(void)
{
	ft_putstr("\033[K");
}
