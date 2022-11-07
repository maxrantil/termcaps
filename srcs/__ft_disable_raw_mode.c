/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_disable_raw_mode.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 17:42:37 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/07 14:09:49 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/**
 * It restores the terminal to its original state
 */
void	ft_disable_raw_mode(void)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &g_orig_termios);
	ft_run_capability("te");
}
