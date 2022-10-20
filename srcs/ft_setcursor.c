/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setcursor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 13:43:20 by mrantil           #+#    #+#             */
/*   Updated: 2022/10/20 13:44:01 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

void ft_setcursor(int row, int col)
{
	char *cm; // cursor move sequence
		
	cm = tgetstr("cm", NULL);
	tputs(tgoto(cm, row, col), 1, ft_putc);
}
