/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_opt_mv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 09:05:53 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/09 09:58:07 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

void	ft_opt_mv(t_term *term)
{
	if (term->ch == 98 || term->ch == 102)
		ft_word_mv(term);
	else if (term->ch == 49)
		ft_line_mv(term);
}
