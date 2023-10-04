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

void    hex(char *str, uint64_t nbr64, uint32_t nbr32, int opt)
{
	int				i;
	int				count;
	char			addr_digit64[17] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	char            addr_digit32[9] = {0,0,0,0,0,0,0,0};

	i = 0;
	if (opt & B64)
	{
		if (nbr64 == 0)
		{
			ft_memset(str, '0', 16);
			return;
		}
		while (nbr64)
		{
			to_hex(nbr64, addr_digit64, i);
			++i;
			nbr64 /= 16;
		}
		count = 16 - (int) ft_strlen(addr_digit64);
		for (int j = 0; j < count; j++)
			str[j] = '0';
		while (--i >= 0)
			str[count++] = addr_digit64[i];
	}
	else
	{
		if (nbr32 == 0)
		{
			ft_memset(str, '0', 8);
			return;
		}
		while (nbr32)
		{
			to_hex(nbr32, addr_digit32, i);
			++i;
			nbr32 /= 16;
		}
		count = 8 - (int) ft_strlen(addr_digit32);
		for (int j = 0; j < count; j++)
			str[j] = '0';
		while (--i >= 0)
			str[count++] = addr_digit32[i];
	}
}
