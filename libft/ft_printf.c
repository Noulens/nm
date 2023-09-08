/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <tnoulens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 19:47:07 by tnoulens          #+#    #+#             */
/*   Updated: 2022/06/13 14:07:46 by tnoulens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_percentage(void)
{
	ft_putchar_fd('%', 1);
	return (1);
}

static	int	ft_print_format(const char *format, va_list arg)
{
	int	j;

	j = 0;
	if (*format == 'd' || *format == 'i')
		return (j = ft_di(va_arg(arg, int)));
	else if (*format == 'c')
		return (j = ft_c(va_arg(arg, int)));
	else if (*format == 'p')
		return (j = ft_p(va_arg(arg, void *)));
	else if (*format == 's')
		return (j = ft_s(va_arg(arg, char *)));
	else if (*format == 'x' || *format == 'X' || *format == 'u')
		return (j = ft_xupx(va_arg(arg, unsigned int), *format));
	else if (*format == '%')
		return (j = ft_percentage());
	else
		return (-1);
}

int	ft_print_default(char c)
{
	ft_putchar_fd(c, 1);
	return (1);
}

int	ft_printf(const char *format, ...)
{
	va_list	arg;
	int		j;
	int		error;

	j = 0;
	va_start(arg, format);
	while (format && *format)
	{
		while (*format != '%' && *format)
		{
			j += ft_print_default(*format);
			++format;
		}
		if (*format == '\0')
			return (j);
		else
			error = ft_print_format(++format, arg);
		if (error == -1)
			return (-1);
		else
			j += error;
		++format;
	}
	va_end(arg);
	return (j);
}

/*#include <stdio.h>

int	main(void)
{
	int		i;
	int		j;
//	int		*p;
//	char	*q;
//	char 	r[] = "FFFF";

	i = 0;
	j = 0;
//	p = &i;
//	q = NULL;
	i = ft_printf(" %s %s %s %s %s ", " - ", "", "4", "", "2 ");
	ft_printf("\n%d\n", i);
	j = printf(" %s %s %s %s %s ", " - ", "", "4", "", "2 ");
	printf("\n%d\n", j);
//		i = ft_printf(" NULL %s NULL ", NULL);
//	ft_printf("\n%d\n", i);
//	j = printf(" NULL %s NULL ", NULL);
//	printf("\n%d\n", j);
	return (0);
}*/
