/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_opts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 19:56:36 by dromansk          #+#    #+#             */
/*   Updated: 2019/09/08 18:40:05 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

int		selchar(int c)
{
	write(1, &c, 1);
	return (c);
}

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

	columnize_opts(sel);
	list = sel->options;
	while (list != sel->options->prev)
	{
		ftgoto(list->col, list->row);
		ft_putstr(list->option);
		list = list->next;
	}
	ftgoto(list->col, list->row);
	ft_putstr(list->option);
	list = list->next;
	ftgoto(0, 0);
	sel->mcol = 0;
	sel->mrow = 0;
	add_colour(sel->options->sel ? REV_ULINE : ULINE, sel->options);
}

void	screen_save_clear(int mode)
{
	static char	buf[1024];

	if (!mode)
	{
		ft_bzero(buf, 1024);
		tgetent(buf, getenv("TERM"));
		ft_do_cap("cl");
	}
	else
		tputs(buf, 1, selchar);
}

void	print_selected(t_select *sel)
{
	t_sel_list	*list;

	if (sel->status % 2)
	{
		while (sel->options->row || sel->options->col)
			sel->options = sel->options->next;
		list = sel->options->next;
		ft_putstr(sel->options->option);
		while (list != sel->options)
		{
			ft_putstr(list->option);
			list = list->next;
		}
	}
	free_sel(sel);
}
