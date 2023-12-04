/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aogbi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 21:08:32 by aogbi             #+#    #+#             */
/*   Updated: 2023/12/04 18:59:57 by aogbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libftprintf.h"

static int	valid(char *base)
{
	int	i;
	int	j;

	i = 0;
	if (ft_strlen(base) < 2)
		return (0);
	while (base[i])
	{
		if (base[i] == '+' || base[i] == '-')
			return (0);
		i++;
	}
	i = 0;
	while (base[i])
	{
		j = i + 1;
		while ((base[i] != base[j]) && base[j])
			j++;
		if (base[i] == base[j])
			return (0);
		i++;
	}
	return (1);
}
static int	ft_putnbr_base(long nbr, char *base, int len)
{
	long	base_len;
	long	n;

	if (!valid(base))
		return (len);
	n = nbr;
	if (nbr < 0)
	{
		ft_putchar_fd('-', 1);
		len++;
		n *= -1;
	}
	base_len = ft_strlen(base);
	if (n < base_len)
	{
		ft_putchar_fd(base[n % base_len], 1);
		len++;
	}
	else
	{
		len = ft_putnbr_base(n / base_len, base, len);
		len = ft_putnbr_base(n % base_len, base, len);
	}
	return (len);
}

int ft_printf(const char *str, ...)
{
	int		len;
	va_list	args;
	void	*x;

	va_start(args, str);

	len = 0;
	while (*str)
	{
		if (*str == '%')
		{
			if (*(str + 1) == 'c')
			{
				x = va_arg(args, void *);
				ft_putchar_fd(*(unsigned char *)&x, 1);
				str++;
				len++;
			}
			else if (*(str + 1) == 's')
			{
				x = va_arg(args, void *);
				len += ft_putstr((char *)x);
				str++;
			}
			else if (*(str + 1) == 'p')
			{
				x = va_arg(args, void *);
				ft_putstr("0x");
				len = ft_putnbr_base((unsigned long long)x, "0123456789abcdef", len) + 2;
				str++;
			}
			else if (*(str + 1) == 'd')
			{
				x = va_arg(args, void *);
				len = ft_putnbr_base(*(int *)&x, "0123456789", len);
				str++;
			}
			else if (*(str + 1) == 'i')
			{
				x = va_arg(args, void *);
				len = ft_putnbr_base(*(int *)&x, "0123456789", len);
				str++;
			}
			else if (*(str + 1) == 'u')
			{
				x = va_arg(args, void *);
				len = ft_putnbr_base(*(unsigned int*)&x, "0123456789", len);
				str++;
			}
			else if (*(str + 1) == 'x')
			{
				x = va_arg(args, void *);
				len = ft_putnbr_base(*(unsigned int*)&x, "0123456789abcdef", len);
				str++;
			}
			else if (*(str + 1) == 'X')
			{
				x = va_arg(args, void *);
				len = ft_putnbr_base(*(unsigned int*)&x, "0123456789ABCDEF", len);
				str++;
			}
			else if (*(str + 1) == '%')
			{
				ft_putchar_fd('%', 1);
				str++;
				len++;
			}
		}
		else
		{
			ft_putchar_fd(*str, 1);
			len++;
		}
		str++;
	}
	return (len);
}
