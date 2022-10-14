/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_movement_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 08:29:54 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/14 08:38:11 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"

void	cursor_beginning(int *cur)
{
	char	*tofree;

	tofree = NULL;
	write(1, "\033[", 2);
	tofree = ft_itoa(*cur);
	write(1, tofree, ft_intlen(*cur));
	ft_strdel(&tofree);
	write(1, "D", 1);
	cur[0] = 0;
}

void	cursor_end(int *cur, int *bytes)
{
	char	*tofree;

	tofree = NULL;
	write(1, "\033[", 2);
	tofree = ft_itoa(*bytes - *cur);
	write(1, tofree, ft_intlen(*bytes - *cur));
	ft_strdel(&tofree);
	write(1, "C", 1);
	cur[0] = *bytes;
}

static void	shift_arrow(int *bytes, int *cur, int *c)
{
	c[0] = get_input();
	c[0] = get_input();
	c[0] = get_input();
	if (*c == 'D' && *cur)
		cursor_beginning(cur);
	if (*c == 'C' && *cur < *bytes)
		cursor_end(cur, bytes);
}

void	esc_parse(char *input, t_termcap *cap)
{
	cap->ch = get_input();
	if (cap->ch == '[')
	{
		cap->ch = get_input();
		if (cap->ch == 'D')
			cap->ch = LEFT;
		if (cap->ch == 'C')
			cap->ch = RIGHT;
		if (cap->ch == 'A')
			cap->ch = UP;
		if (cap->ch == 'B')
			cap->ch = DOWN;
		if (cap->ch == 'H' && cap->cursor)
			cursor_beginning(&cap->cursor);
		if (cap->ch == 'F' && cap->cursor < cap->bytes)
			cursor_end(&cap->cursor, &cap->bytes);
		if (cap->ch == '1')
			shift_arrow(&cap->bytes, &cap->cursor, &cap->ch);
		cursor_mv(cap);
	}
	if (cap->ch == 'b')
		alt_mv_left(&cap->cursor, input);
	if (cap->ch == 'f')
		alt_mv_right(&cap->cursor, input, &cap->bytes);
	cap->ch = 0;
}
