/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 07:52:49 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/14 08:48:01 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"

int	get_input(void)
{
	int	c;

	c = 0;
	read(STDIN_FILENO, &c, 1);
	// printf("c[%d]\n", c);		//save this for testing
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

void	quote_count(int *quote, int *c)
{
	if (!*quote)
		*quote = *c;
	else if (*quote == *c)
		*quote = 0;
}
