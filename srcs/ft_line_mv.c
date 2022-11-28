/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_line_mv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:41:49 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/28 13:02:00 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

void	ft_line_mv(t_term *t)
{
	t->ch = ft_get_input();
	if (t->ch == 59)
	{
		t->ch = ft_get_input();
		if (t->ch == 51)
		{
			t->ch = ft_get_input();
			if (t->ch == 65 && t->c_row && ft_get_linenbr())
				ft_line_up(t);
			if (t->ch == 66 && t->c_row < t->total_row)
				ft_line_down(t);
			t->ch = 0;
		}
	}
}
