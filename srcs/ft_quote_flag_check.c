#include "keyboard.h"

void	ft_quote_flag_check(t_term *t, ssize_t index)
{
	ssize_t i;

	i = index;
	while(t->inp[i] && t->inp[i] == '\\')
		i++;
	if (t->inp[i] == S_QUO || t->inp[i] == D_QUO)
		ft_quote_flag_reset(t);	
}