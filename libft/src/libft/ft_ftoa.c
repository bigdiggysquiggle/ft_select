/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 20:19:02 by dromansk          #+#    #+#             */
/*   Updated: 2019/09/12 23:00:04 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*floatjoin(char **num, char *dec)
{
	char	*res;

	res = ft_strjoin(*num, dec);
	free(*num);
	free(dec);
	return (res);
}

char		*precision(long double dec, size_t prec)
{
	char	*n;
	int		i;

	n = ft_strnew(prec);
	i = 0;
	while (prec-- > 1)
	{
		dec *= 10;
		n[i++] = base_table((int)dec);
	}
	dec += 0.5;
	n[i] = base_table((int)dec);
	return (n);
}

int			nan_comp(double f)
{
	float		test;

	test = 0;
	if (!(f >= test) && !(f <= test))
		return (1);
	return (0);
}

/*
** borrow alan's ideas for your implementation
*/

char		*ft_ftoa(double f, size_t prec)
{
	long long	num;
	long double	d;
	char		*s;

	if (f > DBL_MAX)
		return (ft_strdup("inf"));
	if (f < DBL_MIN)
		return (ft_strdup("-inf"));
	if (nan_comp(f))
		return (ft_strdup("nan"));
	num = (long long)f;
	s = ft_ltoa_base(num, 10);
	d = f < 0 ? -(f - num) : f - num;
	s = swap_n_free(ft_strjoin(s, "."), &s);
	s = floatjoin(&s, precision(d, prec));
	return (s);
}
