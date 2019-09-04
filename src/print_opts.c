/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_opts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 19:56:36 by dromansk          #+#    #+#             */
/*   Updated: 2019/09/04 14:56:28 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

void	add_colour(char *colour, t_sel_list *opts)
{
	char	*s;

	ft_putstr(colour);
	s = tgoto("cm", opts->col + opts->len, opts->row);
	tputs(s, 1, NULL);
	ft_putstr(NORM);
	s = tgoto("cm", opts->col, opts->row);
	tputs(s, 1, NULL);
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
		s = tgoto("cm", list->col, list->row);
		tputs(s, 1, NULL);
		ft_putstr(list->option);
		list = list->next;
	}
	s = tgoto("cm", list->col, list->row);
	tputs(s, 1, NULL);
	ft_putstr(list->option);
	list = list->next;
	s = tgoto("cm", 0, 0);
	tputs(s, 1, NULL);
	sel->mcol = 0;
	sel->mrow = 0;
	add_colour(sel->options->sel ? REV_ULINE : ULINE, sel->options);
}
