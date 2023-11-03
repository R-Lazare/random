#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return(1);
}

int	ft_putstr(char *src)
{
	int i = 0;
	if (!src)
	{
		write(1, "(null)", 6);
		return(6);
	}
	while (src[i])
	{
		write(1, &src[i], 1);
		i++;
	}
	return(i);
}

int	ft_putnbr(int nb, int i)
{
	if (nb == -2147483648)
	{
		write(1, "-2147483648", 11);
		return(11);
	}
	if (nb < 0)
	{
		write(1, "-", 1);
		i++;
		nb = -nb;
	}
	if (nb > 9)
		i = i + ft_putnbr(nb / 10, i);
	i = i + ft_putchar(nb % 10 + '0');
	return (i);
}

int	ft_putnbr_base(unsigned int nb, char *base, unsigned int size, int i)
{
	if (nb >= size)
		i = i + ft_putnbr_base(nb / size, base, size, i);
	i = i + ft_putchar(base[nb % size]);
	return(i);
}

int	ft_pourcent(const char *src, va_list list, int i )
{
	int nb = 0;
	if (src[i] == 's')
		nb = nb + ft_putstr(va_arg(list, char *));
	else if (src[i] == 'd')
		nb = nb + ft_putnbr(va_arg(list, int), 0);
	else if (src[i] == 'x')
		nb = nb + ft_putnbr_base(va_arg(list, int), "0123456789abcdef", 16, 0);
	return(nb);
}

int	ft_printf(const char *src, ...)
{
	int i = 0;
	int nb = 0;
	va_list list;
	va_start(list, src);
	
	while(src[i])
	{
		if (src[i] == '%')
		{
			i++;
			nb = nb + ft_pourcent(src, list, i);
		}
		else
			nb = nb + ft_putchar(src[i]);
		i++;
	}
	va_end(list);
	return(nb);
}
