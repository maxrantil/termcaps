/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_opt_mv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 09:05:53 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/08 13:57:04 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/**
 * It moves the cursor to the beginning or end of the line, or to the
 * beginning or end of the word
 * 
 * @param term the term struct
 * @param input the string that the user is editing
 */
void	ft_opt_mv(t_term *term, char *input)
{
	if (term->ch == 98 || term->ch == 102)
		ft_word_mv(term, input);
	else if (term->ch == 49)
		ft_line_mv(term, input);
}
