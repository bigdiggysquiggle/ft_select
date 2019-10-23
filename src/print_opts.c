/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_opts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 19:56:36 by dromansk          #+#    #+#             */
/*   Updated: 2019/10/23 13:13:10 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

void	add_colour(char *colour, t_sel_list *opts)
{
	ft_putstr(colour);
	ftgoto(opts->col + opts->len, opts->row);
	ft_putstr(NORM);
	ftgoto(opts->col, opts->row);
}

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
	list = sel->first;
//	ft_printf("padding: %d\n", space);//
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
