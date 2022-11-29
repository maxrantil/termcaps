/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_line_mv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:41:49 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/29 15:30:12 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

void	ft_line_mv(t_term *t)
{
	t->ch = ft_get_input();
	if (t->ch == ';')
	{
		t->ch = ft_get_input();
		if (t->ch == '3')
		{
			t->ch = ft_get_input();
			if (t->ch == ARROW_UP && t->c_row && ft_get_linenbr())
				ft_line_up(t);
			if (t->ch == ARROW_DOWN && t->c_row < t->total_row)
				ft_line_down(t);
			t->ch = 0;
		}
	}
}
