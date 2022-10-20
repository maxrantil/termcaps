/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cursor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:33:48 by mrantil           #+#    #+#             */
/*   Updated: 2022/10/20 12:36:13 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

void	ft_cursor_right(t_term *cap)
{
	if (cap->cursor)
		cap->cursor++;
	write(1, "\033[1C", 4);
}

void	ft_cursor_left(t_term *cap)
{
	if (cap->cursor)
		cap->cursor--;
	write(1, "\033[1D", 4);
}

void	ft_cursor_up(t_term *cap)
{
	if (cap->cur_row)
		cap->cur_row--;
	write(1, "\033[1A", 4);
}

void	ft_cursor_down(t_term *cap)
{
	cap->cur_row++;
	write(1, "\033[1B", 4);
}

void	ft_cursor_beginning(int *cur)
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

void	ft_cursor_end(int *cur, int *bytes)
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

void	ft_cursor_mv(t_term *term)
{
	if (term->ch== LEFT && term->cursor)
		ft_cursor_left(term);
	if (term->ch== RIGHT && (term->cursor < term->bytes))
		ft_cursor_right(term);
	if (term->ch== DOWN && (term->cur_row < term->row))
		ft_cursor_down(term);
	if (term->ch== UP && (term->cur_row > 0))
		ft_cursor_up(term);
}
