/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 20:48:15 by dromansk          #+#    #+#             */
/*   Updated: 2019/10/22 17:41:26 by dromansk         ###   ########.fr       */
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
	prev->next = next;
	next->prev = prev;
	next->sel |= 2;
	sel->options = next;
	print_opts(sel);
}

void	select_item(t_select *sel)
{
	sel->options->sel = sel->options->sel & 1 ? 0 : 1;
	print_opts(sel);
}

/*
** convert these two so they can find the currently selected item,
** remove ul, move to next option, add ul
*/

void	move_hor(t_select *sel, t_sel_list *opt)
{
	sel->options->sel &= ~2;
	opt->sel |= 2;
	sel->options = opt;
	print_opts(sel);
}

void	move_ver(t_select *sel, int up)
{
	int		move;

	move = 0;
	sel->options->sel &= ~2;
	while (move < sel->col_count)
	{
		sel->options = up ? sel->options->prev : sel->options->next;
		move++;
	}
	sel->options->sel |= 2;
	print_opts(sel);
}
