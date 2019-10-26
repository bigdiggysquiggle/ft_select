/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 03:38:35 by dromansk          #+#    #+#             */
/*   Updated: 2019/10/26 04:05:14 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

void	repchar(char c, int i)
{
	while (i--)
		write(STDIN_FILENO, &c, 1);
}

void	sec_flip(char *s, int rev)
{
	int	i;

	if (!rev)
		ft_putstr_fd(s, STDIN_FILENO);
	else
	{
		i = ft_strlen(s);
		while (i--)
			ft_putchar_fd(s[i], STDIN_FILENO);
	}
}
