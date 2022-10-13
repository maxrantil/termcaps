/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 09:23:01 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/13 14:51:06 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"

void	delete(char *input, int *bytes, int *cur)
{
	deletion_shift(input, bytes, cur, DEL);
	clear_trail();
	print_trail(input, *cur);
}

void	backspace(char *input, int *bytes, int *cur)
{
	cursor_left(NULL);
	clear_trail();
	if (*cur == *bytes)
	{
		bytes[0]--;
		cur[0]--;
		input[*cur] = '\0';
	}
	else
		deletion_shift(input, bytes, cur, BCK);
	if (input[*cur])
		print_trail(input, *cur);
}

void	cursor_mv(int *bytes, int *cur, int c)
{
	if (c == LEFT && *cur)
		cursor_left(cur);
	if (c == RIGHT && (*cur < *bytes))
		cursor_right(cur);
}

void	char_print(char *input, int *bytes, int *cur, int c)
{
	write(1, &c, 1);
	if (input[*cur])
		insertion_shift(input, bytes, *cur);
	input[cur[0]++] = c;
	if (input[*cur])
		print_trail(input, *cur);
	bytes[0]++;
}

void	esc_parse(char *input, int *bytes, int *cur, int *c)
{
	c[0] = get_input();
	if (*c == '[')
	{
		c[0] = get_input();
		if (*c == 'D')
			*c = LEFT;
		if (*c == 'C')
			*c = RIGHT;
		if (*c == 'H' && *cur)
			cursor_beginning(cur);
		if (*c == 'F' && *cur < *bytes)
			cursor_end(cur, bytes);
		if (*c == '1') // when shift is pressed
		{
			c[0] = get_input();
			c[0] = get_input();
			c[0] = get_input();
			if (*c == 'D' && *cur)
				cursor_beginning(cur);
			if (*c == 'C' && *cur < *bytes)
				cursor_end(cur, bytes);
		}
		cursor_mv(bytes, cur, *c);
	}
	if (*c == 'b')
		alt_mv_left(cur, input);
	if (*c == 'f')
		alt_mv_right(cur, input, bytes);
	c[0] = 0;
}
