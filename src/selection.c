/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 20:48:15 by dromansk          #+#    #+#             */
/*   Updated: 2019/10/25 22:27:10 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

void	del_item(t_select *sel)
{
	t_sel_list	*prev;
	t_sel_list	*next;
	t_sel_list	*rm;

	rm = sel->options;
	prev = rm->prev;
	next = rm->next;
	if (next == next->next)
	{
		sel->first = NULL;
		sel->options = NULL;
		sel->status = 2;
	}
	else
	{
		prev->next = next;
		next->prev = prev;
		sel->options = rm->next == sel->first ? prev : next;
		if (rm == sel->first)
			sel->first = next;
		print_opts(sel);
	}
	free(rm);
}

void	select_item(t_select *sel)
{
	sel->options->sel = sel->options->sel ? 0 : 1;
	sel->options = sel->options->next;
	print_opts(sel);
}

void	invert_selection(t_select *sel)
{
	t_sel_list	*list;

	list = sel->first;
	list->sel = list->sel == 0;
	list = list->next;
	while (list != sel->first)
	{
		list->sel = list->sel == 0;
		list = list->next;
	}
	print_opts(sel);
}

void	move_hor(t_select *sel, int left)
{
	sel->options = left ? sel->options->prev : sel->options->next;
	print_opts(sel);
}

void	move_ver(t_select *sel, int up)
{
	int		pos;

	pos = sel->options->col;
	sel->options = up ? sel->options->prev : sel->options->next;
	while (sel->options->col != pos)
		sel->options = up ? sel->options->prev : sel->options->next;
	print_opts(sel);
}
