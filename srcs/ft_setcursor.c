/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setcursor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 13:43:20 by mrantil           #+#    #+#             */
/*   Updated: 2022/10/20 14:05:04 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

void	ft_setcursor(int col, int row)
{
	char	*cm;

	cm = tgetstr("cm", NULL);
	tputs(tgoto(cm, col, row), 1, ft_putc);
}
