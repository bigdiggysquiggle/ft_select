/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_opts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 19:56:36 by dromansk          #+#    #+#             */
/*   Updated: 2019/10/24 22:33:37 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

/*
** print colours on redraw
*/

void	print_item(t_sel_list *list, int ul)
{
	ftgoto(list->col, list->row);
	if (list->sel)
		ft_dprintf(0, "%s", REV);
	if (ul)
		ft_dprintf(0, "%s", ULINE);
	ft_dprintf(0, "%s", list->option);
	ft_dprintf(0, "%s", NORM);
}

void	print_opts(t_select *sel)
{
	t_sel_list	*list;

	ft_do_cap("cl");
	columnize_opts(sel);
	if (sel->col_count < 0)
	{
		ft_printf("Window tooo smoll :(");
		return ;
	}
	list = sel->first;
	print_item(list, list == sel->options);
	list = list->next;
	while (list != sel->first)
	{
		print_item(list, list == sel->options);
		list = list->next;
		if (!list->col)
			ft_printf("\n");
	}
}

void	print_selected(t_select *sel)
{
	t_sel_list	*list;
	int			flag;

	flag = 0;
	if (sel->status % 2)
	{
		list = sel->first;
		if (list->sel)
		{
			ft_putstr(list->option);
			flag = 1;
		}
		list = list->next;
		while (list != sel->first)
		{
			if (list->sel)
			{
				ft_printf(flag ? " %s" : "%s", list->option);
				flag = 1;
			}
			list = list->next;
		}
	}
	free_sel(sel);
}
