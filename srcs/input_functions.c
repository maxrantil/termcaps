/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 09:23:01 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/12 13:17:25 by mbarutel         ###   ########.fr       */
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

void	cursor_mv(int *i, int *cur, int c)
{
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

void	esc_parse(char *input, int *i, int *cur, int *c)
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
		if (*c == 'F' && *cur < *i)
			cursor_end(cur, i);
		if (*c == '1') // when shift is pressed
		{
			c[0] = get_input();
			c[0] = get_input();
			c[0] = get_input();
			if (*c == 'D' && *cur)
				cursor_beginning(cur);
			if (*c == 'C' && *cur < *i)
				cursor_end(cur, i);
		}
		cursor_mv(i, cur, *c);
	}
	if (*c == 'b')
		alt_mv_left(cur, input);
	if (*c == 'f')
		alt_mv_right(cur, input, i);
	c[0] = 0;
}
