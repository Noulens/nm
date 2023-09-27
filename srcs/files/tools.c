//
// Created by tnoulens on 9/26/23.
//

#include "ft_nm.h"

static void	to_hex(unsigned long addr, char *digit, int i)
{
		digit[i] = (char)(addr % 16);
		if (digit[i] < 10)
			digit[i] += 48;
		else
			digit[i] += 87;
}

void    hex(char *str, unsigned long nbr)
{
	int				i;
	int				count;
	char			addr_digit[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};;

	i = 0;
	if (nbr == 0)
	{
		str[0] = '0';
		return ;
	}
	while (nbr)
	{
		to_hex(nbr, addr_digit, i);
		++i;
		nbr /= 16;
	}
	count = 0;
	while (--i >= 0)
		str[count++] = addr_digit[i];
}
