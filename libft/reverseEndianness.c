/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverseEndianness.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <tnoulens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 19:47:07 by tnoulens          #+#    #+#             */
/*   Updated: 2022/10/04 15:31:08 by tnoulens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void    reverseEndianness(void *data, int size)
{
	uint8_t *bytes;
	uint8_t temp;
	int     nb;
	int     i;

	bytes = (uint8_t *)data;
	nb = size / 2;
	i = 0;
	while (i < nb)
	{
		temp = bytes[i];
		bytes[i] = bytes[size - 1 - i];
		bytes[size - 1 - i] = temp;
		i++;
	}
}
