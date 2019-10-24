/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 18:25:42 by dromansk          #+#    #+#             */
/*   Updated: 2019/10/23 19:25:43 by dromansk         ###   ########.fr       */
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

int				selchar(int c)
{
	t_select	*sel;

	sel = store_sel(0);
	write(sel->termfd, &c, 1);
	return (c);
}

int				sel_list_len(t_sel_list *sel)
{
	t_sel_list	*curr;
	int			count;

	count = 1;
	curr = sel->next;
	while (curr != sel)
	{
		curr = curr->next;
		count++;
	}
	return (count);
}
