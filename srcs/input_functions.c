/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 09:23:01 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/12 09:50:58 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"

void	delete(char *input, int *i, int *cur)
{
	deletion_shift(input, i, cur, DEL);
	clear_trail();
	print_trail(input, *cur);
}

void	backspace(char *input, int *i, int *cur)
{
	cursor_left(NULL);
	clear_trail();
	if (*cur == *i)
	{
		i[0]--;
		cur[0]--;
		input[*cur] = '\0';
	}
	else
		deletion_shift(input, i, cur, BCK);
	if (input[*cur])
		print_trail(input, *cur);
}

void	cursor_mv(char *input, int *i, int *cur, int c)
{
	c = get_input();
	if (c == '[')
	{
		c = get_input();
		if (c == 'D')
			c = LEFT;
		if (c == 'C')
			c = RIGHT;
	}
	if (c == 'b')
		alt_mv_left(cur, input);
	if (c == 'f')
		alt_mv_right(cur, input, i);
	if (c == LEFT && *cur)
		cursor_left(cur);
	if (c == RIGHT && (*cur < *i))
		cursor_right(cur);
}

void	char_print(char *input, int *i, int *cur, int c)
{
	write(1, &c, 1);
	if (input[*cur])
		insertion_shift(input, i, *cur);
	input[cur[0]++] = c;
	if (input[*cur])
		print_trail(input, *cur);
	i[0]++;
}
