/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_capability.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 13:41:44 by mrantil           #+#    #+#             */
/*   Updated: 2022/10/20 16:07:59 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

void	run_capability(char *cap)
{
	char	*p;
	
	p = tgetstr(cap, NULL);
	if (p == NULL)
		ft_putendl_fd("error, cannot run_capability", 2);
	else
		tputs(p, 1, ft_putc);
}
