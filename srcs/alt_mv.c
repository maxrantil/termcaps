/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cursor_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 09:05:53 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/20 12:07:59 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

void	alt_mv_left(t_term *term, char *input)
{
	while (term->c_col > 0 && ft_isspace(&input[term->c_col - 1]))
		term->c_col--;
	while (term->c_col > 0 && !ft_isspace(&input[term->c_col - 1]))
		term->c_col--;
	ft_setcursor(term->c_col, term->c_row);
}

void	alt_mv_right(t_term *term, char *input)
{
	while (term->c_col < term->bytes && ft_isspace(&input[term->c_col]))
		term->c_col++;
	while (term->c_col < term->bytes && !ft_isspace(&input[term->c_col]))
		term->c_col++;
	ft_setcursor(term->c_col, term->c_row);
}
