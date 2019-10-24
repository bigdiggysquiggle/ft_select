/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 20:48:15 by dromansk          #+#    #+#             */
/*   Updated: 2019/10/24 14:12:46 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

void	del_item(t_select *sel)
{
	t_sel_list	*prev;
	t_sel_list	*next;

	prev = sel->options->prev;
	next = sel->options->next;
	free(sel->options);
	if (next == prev)
	{
		sel->first = NULL;
		sel->options = NULL;
		sel->status = 2;
	}
	else
	{
		prev->next = next;
		next->prev = prev;
		if (sel->options == sel->first)
			sel->first = next;
		sel->options = next;
		print_opts(sel);
	}
}

void	select_item(t_select *sel)
{
	sel->options->sel = sel->options->sel ? 0 : 1;
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
