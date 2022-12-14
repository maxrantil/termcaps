/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nl_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 15:00:30 by mbarutel          #+#    #+#             */
/*   Updated: 2022/12/14 14:39:01 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/**
 * It removes the newline character from the history buffer if it's preceded 
 * by a backslash or if it's the last character in the buffer
 * 
 * @param t the term structure
 */
int ft_nl_removal_bslash_check(t_term *t, ssize_t pos)
{
	ssize_t	start;
	ssize_t	count;
	
	start = pos - 1;
	while (start && t->history_buff[start] == '\\')
		start--;
	if (start)
		start++;
	count = start;
	while (count < t->bytes && t->history_buff[count] == '\\') 
		count++;
	if ((count - start) % 2)
		return (1);
	return (0);
}

void	ft_nl_removal(t_term *t)
{
	int		k;
	int		i;
	char	quote;

	k = -1;
	quote = 0;
	while (t->history_buff[++k])
	{
		if (t->history_buff[k] == '\n' && !quote)
		{
			
			if (k < 1 || t->history_buff[k - 1] == '\\')
				i = k + 2;
		}
		else
		{
			if ((t->history_buff[k] == '\'' || t->history_buff[k] == '\"') && !ft_nl_removal_bslash_check(t, k))
			{
				if (quote == 0)
					quote = t->history_buff[k];
				else if (quote == t->history_buff[k])
					quote = 0;		
			}
			i = k;
		}
		ft_memmove((void *)&t->history_buff[k], (void *)&t->history_buff[i], ft_strlen(&t->history_buff[i]) + 1);
	}
}

// BASH:keyboard$  echo "carl\
// > mike\
// > aasda"
// carlmikeaasda
// BASH:keyboard$  echo "carl\
// mike\
// aasda"
// carlmikeaasda
// BASH:keyboard$ echo mike\
// > caslr\
// > asdas\
// > asdasd
// mikecaslrasdasasdasd
// BASH:keyboard$ echo mikecaslrasdasasdasd

// if a backslash is inside qoutes they are kept in the string to history vec_push
// if a backslash is not inside qoute, they are skipped, along with the newline character that is after it IF it exists
