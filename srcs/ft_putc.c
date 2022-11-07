/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:19:49 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/07 16:04:50 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/**
 * It writes a single character to the standard output.
 * 
 * @param c The character to print.
 * 
 * @return The number of bytes written to the file descriptor.
 */
int	ft_putc(int c)
{
	return (write(1, &c, 1));
}
