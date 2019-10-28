/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_opts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 19:56:36 by dromansk          #+#    #+#             */
/*   Updated: 2019/10/26 03:25:21 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

/*
** print colours on redraw
*/

static void	print_item(t_sel_list *list, int ul)
{
	ftgoto(list->col, list->row);
	ft_dprintf(STDIN_FILENO, list->sel ? "\033[38;5;81m" :
			"\033[38;5;57m");
	if (list->sel)
		ft_dprintf(STDIN_FILENO, "%s", REV);
	if (ul)
		ft_dprintf(STDIN_FILENO, "%s", ULINE);
	ft_dprintf(STDIN_FILENO, "%s", list->option);
	ft_dprintf(STDIN_FILENO, "%s", NORM);
}

void		print_opts(t_select *sel)
{
	t_sel_list	*list;

	ft_do_cap("cl");
	columnize_opts(sel);
	if (sel->col_count < 0)
	{
		ftgoto(sel->ws->ws_col / 2 - 10, sel->ws->ws_row / 2);
		ft_dprintf(STDERR_FILENO, "Window tooo smoll :(");
		return ;
	}
	list = sel->first;
	print_item(list, list == sel->options);
	list = list->next;
	while (list != sel->first)
	{
		print_item(list, list == sel->options);
		list = list->next;
	}
	ftgoto(0, list->prev->row + 2);
	ft_dprintf(STDIN_FILENO, "\033[38;5;226mH: print help%s",
			NORM);
}

void		print_selected(t_select *sel)
{
	t_sel_list	*list;
	int			flag;

	flag = 0;
	if (sel->status % 2)
	{
		list = sel->first;
		if (list->sel)
		{
			ft_putstr_fd(list->option, STDOUT_FILENO);
			flag = 1;
		}
		list = list->next;
		while (list != sel->first)
		{
			if (list->sel)
			{
				ft_dprintf(STDOUT_FILENO, flag ? " %s" : "%s", list->option);
				flag = 1;
			}
			list = list->next;
		}
	}
	free_sel(sel);
}
