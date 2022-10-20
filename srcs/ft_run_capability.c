/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run_capability.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 13:41:44 by mrantil           #+#    #+#             */
/*   Updated: 2022/10/20 16:44:14 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

void	ft_run_capability(char *cap)
{
	char	*p;

	p = tgetstr(cap, NULL);
	if (p == NULL)
	{
		ft_putstr_fd("error: ", 2);
		ft_putstr_fd(cap, 2);
		ft_putstr_fd(" : cannot ft_run_capability()", 2);
	}
	else
		tputs(p, 1, ft_putc);
}
