/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 18:25:42 by dromansk          #+#    #+#             */
/*   Updated: 2019/09/08 18:29:58 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

void			ft_do_cap(char *cap)
{
	char	*s;

	s = tgetstr(cap, NULL);
	tputs(s, 1, selchar);
}

void			ftgoto(int col, int row)
{
	char	*s;

	s = tgetstr("cm", NULL);
	s = tgoto(s, col, row);
	tputs(s, 1, selchar);
}
