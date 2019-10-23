/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_opts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 19:56:36 by dromansk          #+#    #+#             */
/*   Updated: 2019/10/22 18:19:53 by dromansk         ###   ########.fr       */
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

void	print_item(t_sel_list *list, int space)
{
	if (list->sel & 1)
		ft_printf("%s", REV);
	if (list->sel & 2)
		ft_printf("%s", ULINE);
	ft_printf("%s", list->option);
	if (list->sel)
		ft_printf("%s", NORM);
	ft_printf("%-*c", space, 0);
}

void	print_opts(t_select *sel)
{
	t_sel_list	*list;
	int			space;

	ft_do_cap("cl");
	list = sel->options;
	while (list->col || list->row)
		list = list->next;
	space = columnize_opts(sel, list);
//	ft_printf("padding: %d\n", space);//
	print_item(list, space);
	list = list->next;
	while (list != sel->options)
	{
		print_item(list, space);
		list = list->next;
		if (!list->col)
			ft_printf("\n");
	}
//	ftgoto(0, 0);
//	sel->mcol = 0;
//	sel->mrow = 0;
//	ft_printf("%s", sel->options->sel ? REV_ULINE : ULINE);
//	ft_do_cap("us");
//	if (sel->options->sel)
//		ft_do_cap("mr");
//	ftgoto(sel->mcol + sel->options->len, 0);
//	ft_do_cap("ue");
//	ft_printf("%s\n", NORM);
//	add_colour(sel->options->sel ? REV_ULINE : ULINE, sel->options);
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
