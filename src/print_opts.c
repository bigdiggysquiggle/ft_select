/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_opts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 19:56:36 by dromansk          #+#    #+#             */
/*   Updated: 2019/09/05 20:42:47 by dromansk         ###   ########.fr       */
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
	char	*s;

	ft_putstr(colour);
	s = tgoto("CM", opts->col + opts->len, opts->row);
	tputs(s, 1, selchar);
	ft_putstr(NORM);
	s = tgoto("CM", opts->col, opts->row);
	tputs(s, 1, selchar);
}

/*
** print colours on redraw
*/

void	print_opts(t_select *sel)
{
	t_sel_list	*list;
	char		*s;

	columnize_opts(sel);
	list = sel->options;
	while (list != sel->options->prev)
	{
		s = tgoto("CM", list->col, list->row);
		tputs(s, 1, selchar);
		ft_putstr(list->option);
		list = list->next;
	}
	s = tgoto("CM", list->col, list->row);
	tputs(s, 1, selchar);
	ft_putstr(list->option);
	list = list->next;
	s = tgoto("CM", 0, 0);
	tputs(s, 1, selchar);
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
	free_sel(sel);
}
