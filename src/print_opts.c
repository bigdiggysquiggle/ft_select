/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_opts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 19:56:36 by dromansk          #+#    #+#             */
/*   Updated: 2019/09/03 20:51:55 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

void	print_opts(t_select *sel)
{
	t_sel_list	*list;
	char		*s;

	columnize_opts(sel->options);
	list = sel->options;
	while (list)
	{
		s = tgoto("cm", list->col, list->row);
		tputs(s, 1);
		//print option here
		list = list->next;
	}
	sel->mcol = 0;
	sel->mrow = 0;
}
