/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_opts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 19:56:36 by dromansk          #+#    #+#             */
/*   Updated: 2019/10/15 15:34:08 by dromansk         ###   ########.fr       */
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

void	print_opts(t_select *sel)
{
	t_sel_list	*list;
	int			space;

	space = columnize_opts(sel);
	list = sel->options;
	ft_do_cap("cl");
	if (list->sel)
		ft_printf("%s%-*s%s", REV, space, list->option, NORM);
	else
		ft_printf("%-*s", space, list->option);
	list = list->next;
	while (list != sel->options)
	{
		if (list->sel)
			ft_printf("%s%-*s%s", REV, space, list->option, NORM);
		else
			ft_printf("%-*s", space, list->option);
		list = list->next;
		if (!list->col)
			ft_printf("\n");
	}
	ftgoto(0, 0);
	sel->mcol = 0;
	sel->mrow = 0;
	add_colour(sel->options->sel ? REV_ULINE : ULINE, sel->options);
}

void	print_selected(t_select *sel)
{
	t_sel_list	*list;

	if (sel->status % 2)
	{
		while (sel->options->row || sel->options->col)
			sel->options = sel->options->next;
		list = sel->options->next;
		if (sel->options->sel)
			ft_putstr(sel->options->option);
		while (list != sel->options)
		{
			if (sel->options->sel)
				ft_putstr(list->option);
			list = list->next;
		}
	}
	free_sel(sel);
}
