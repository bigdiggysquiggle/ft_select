/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 20:48:15 by dromansk          #+#    #+#             */
/*   Updated: 2019/09/05 20:43:43 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

void	del_item(t_select *sel)
{
	t_sel_list	*prev;
	t_sel_list	*next;

	prev = sel->options->prev;
	next = sel->options->next;
	free(sel->options->prev);
	print_opts(sel);
}

void	select_item(t_select *sel)
{
	int		select;

	select = sel->options->sel;
	if (select)
	{
		add_colour(ULINE, sel->options);
		sel->options->sel = 0;
	}
	else
	{
		add_colour(REV_ULINE, sel->options);
		sel->options->sel = 1;
	}
	// has to move to next item
}

void	move_hor(t_select *sel, t_sel_list *opt)
{
	char	*s;

	add_colour(sel->options->sel ? REV : NORM, sel->options);
	s = tgoto("CM", opt->col, opt->row);
	tputs(s, 1, selchar);
	sel->options = opt;
	sel->mcol = opt->col;
	sel->mrow = opt->row;
	add_colour(opt->sel ? REV_ULINE : ULINE, opt);
}

void	move_ver(t_select *sel, int up)
{
	int		move;
	char	*s;

	move = 0;
	add_colour(sel->options->sel ? REV : NORM, sel->options);
	while (move < sel->col_count)
	{
		sel->options = up ? sel->options->prev : sel->options->next;
		s = tgoto("CM", sel->options->col, sel->options->row);
		tputs(s, 1, selchar);
	}
	sel->mcol = sel->options->col;
	sel->mrow = sel->options->row;
	add_colour(sel->options->sel ? REV_ULINE : ULINE, sel->options);
}
