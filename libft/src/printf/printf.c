/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 14:33:12 by dromansk          #+#    #+#             */
/*   Updated: 2019/11/05 04:06:22 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <printf.h>

int		ft_printf(const char *restrict format, ...)
{
	va_list args;
	int		printed;

	va_start(args, format);
	printed = make_string(0, format, &args, 1);
	va_end(args);
	return (printed);
}

int		ft_dprintf(int fd, const char *restrict format, ...)
{
	va_list args;
	int		printed;

	va_start(args, format);
	printed = make_string(0, format, &args, fd);
	va_end(args);
	return (printed);
}

int		ft_asprintf(char **ret, const char *format, ...)
{
	va_list	args;
	int		printed;

	va_start(args, format);
	*ret = NULL;
	printed = make_string(ret, format, &args, 0);
	va_end(args);
	return (printed);
}

int		ft_sprintf(char *restrict str, const char *restrict format, ...)
{
	va_list	args;
	int		printed;

	va_start(args, format);
	printed = make_string((char **)&str, format, &args, 0);
	va_end(args);
	return (printed);
}
