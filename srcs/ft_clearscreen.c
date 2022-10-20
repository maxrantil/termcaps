/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clearscreen.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 13:41:44 by mrantil           #+#    #+#             */
/*   Updated: 2022/10/20 13:42:46 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

void ft_clearscreen(void)
{
	char *cl;
	
	cl = tgetstr("cl", NULL);
	if (cl == NULL)
		ft_putendl_fd("error, cannot clear the screen", 2);
	else 
		tputs(cl, 1, ft_putc);
}
