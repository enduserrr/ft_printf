#include "ft_printf.h"

int	ft_find_format(char type, va_list ap, int tmp)
{
	int	count;

	count = 0;
	if (type == 'c')
		tmp = ft_print_char(va_arg(ap, int));
	else if (type == 's')
		tmp = ft_print_str(va_arg(ap, char *));
	else if (type == 'p')
		tmp = ft_print_ptr(va_arg(ap, unsigned long));
	else if (type == 'd' || type == 'i')
		tmp = ft_print_dg((long) va_arg(ap, int), "0123456789");
	else if (type == 'u')
		tmp = ft_print_dg((long) va_arg(ap, unsigned int), "0123456789");
	else if (type == 'x')
		tmp = ft_print_dg((long) va_arg(ap, unsigned int), "0123456789abcdef");
	else if (type == 'X')
		tmp = ft_print_dg((long) va_arg(ap, unsigned int), "0123456789ABCDEF");
	else
		tmp = write(1, &type, 1);
	if (tmp == -1)
	{
		va_end(ap);
		return (-1);
	}
	return (count += tmp);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		count;
	int		tmp;
	int		tmp2;

	va_start(ap, format);
	count = 0;
	while (*format)
	{
		tmp = 0;
		tmp2 = 0;
		if (*format == '%')
			tmp = ft_find_format(*(++format), ap, tmp);
		else
			tmp2 = write(1, format, 1);
		if (tmp == -1 || tmp2 == -1)
		{
			count = -1;
			break ;
		}
		format++;
		count += tmp + tmp2;
	}
	va_end(ap);
	return (count);
}
